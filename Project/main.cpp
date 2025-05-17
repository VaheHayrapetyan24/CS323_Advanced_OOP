#include <SFML/Graphics.hpp>
#include <iostream>

#include "body_segment.h"
#include "point.h"
#include "line.h"
#include "body.h"
#include "body_visitor.h"
#include "obj.h"

#include "movement/parallel_movement.h"
#include "animate.h"

bool is_point_in_circle(Point p, Point c, float r) {
    
    float dx = p.get_x() - c.get_x();
    float dy = p.get_y() - c.get_y();
    return (dx * dx + dy * dy) <= (r * r);
}

float get_spine_rotation_angle(Point& hip, Point& shoulder, Point& obj_center, float arm_reach) {
    float slope = hip.dir(shoulder);
    float diff = slope - M_PI_2;
    float dist = hip.dist(shoulder);
    for (; slope > -M_PI_2; slope -= 0.001) {
        float x = hip.get_x() + dist * cos(slope);
        float y = hip.get_y() + dist * sin(slope);
        if (is_point_in_circle(Point(x, y), obj_center, arm_reach)) {
            return slope - diff;
        }
    }
    return 0;
}

float get_arm_rotation_angle(Point shoulder, Point hip, Point& obj_center, float arm_reach, float spine_slope) {
    shoulder.rotate_around(hip.get_x(), hip.get_y(), spine_slope);
    return shoulder.dir(obj_center);
}

int main()
{

    float body_x_diff = 300;
    Body body(body_x_diff, 0);
    

    int x, y;
    while (true) {
        std::cout << "Enter x coordinate (0 < x < 950): ";
        std::cin >> x;
        std::cout << "Enter y coordinate (50 < y < 1950): ";
        std::cin >> y;

        x += body_x_diff;
        printf("%d, %d, %d\n", x, y, (int)body.get_r_foot().get_line().get_end().get_x());

        if (x > (int) body.get_r_foot().get_line().get_end().get_x() && x < 1450 && y > 50 && y < 1950) {
            break;
        } else {
            std::cout << "Invalid coordinates. Please try again.\n";
        }
    }

    sf::RenderWindow window(sf::VideoMode(2000, 2000), "Line Example");
    Body_drawer bd(window, 1000);

    Obj obj(Point((float)x, (float)y), 50, 1000);
    Animate animator(body);

    std::unique_ptr<Movement_iterator> walking_movement = animator.step_forward_iterator();
    std::unique_ptr<Movement_iterator> stand_upright_movement = animator.stand_upright_iterator();

    Parallel_movement grabbing_movement(body);

    float arm_reach = body.get_r_humerus().get_line().length() + body.get_r_radius().get_line().length();

    float x_diff = obj.get_center().get_x() - arm_reach - body.get_r_clavicle().get_line().get_end().get_x();
    Point future_shoulder = Point(body.get_r_clavicle().get_line().get_end().get_x() + x_diff, body.get_r_clavicle().get_line().get_end().get_y());
    Point future_hip = Point(body.get_spine().get_line().get_start().get_x() + x_diff, body.get_spine().get_line().get_start().get_y());
    float spine_angle = get_spine_rotation_angle(future_hip, future_shoulder, obj.get_center(), arm_reach);

    float arm_angle = get_arm_rotation_angle(future_shoulder, future_hip, obj.get_center(), arm_reach, spine_angle - M_PI_2);
    grabbing_movement.add_movement(std::make_unique<Basic_movement>(
        body, spine_angle, 400,
        [](Body& body, float target) { 
            body.get_spine().rotate(target);
        },
        [](Body& body) { return body.get_spine().slope(); }
    ).release());
    grabbing_movement.add_movement(std::make_unique<Basic_movement>(
        body, arm_angle, 400,
        [](Body& body, float target) {
            body.get_r_humerus().rotate(target);
        },
        [](Body& body) { return body.get_r_humerus().slope(); }
    ).release());

    grabbing_movement.add_movement(std::make_unique<Basic_movement>(
        body, arm_angle, 400,
        [](Body& body, float target) { 
            body.get_r_radius().rotate(target);
        },
        [](Body& body) { return body.get_r_radius().slope(); }
    ).release());

    std::unique_ptr<Movement_iterator> grab = grabbing_movement.initiate();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        bd.visit(&body);

        
        Line spine = body.get_spine().get_line();

        if (obj.get_center().get_x() - spine.get_start().get_x() > arm_reach + body.get_r_clavicle().get_line().length()) {
            if (!walking_movement->make_step()) {
                walking_movement = animator.step_forward_iterator();
            }
        } else {
            if (!stand_upright_movement->make_step()) {
                if (!grab->make_step()) {
                    break;
                }
            }
        }

        obj.draw(window);
        window.display();
    }

    

    return 0;
}