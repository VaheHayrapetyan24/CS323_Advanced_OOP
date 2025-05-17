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

#define X_PIXELS 2000
#define Y_PIXELS 1200

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
    int max_x = X_PIXELS - 2 * body_x_diff - 2 * OBJ_RADIUS;
    int max_y = BODY_HEIGHT;
    while (true) {
        std::cout << "Enter x coordinate (0 < x < " << max_x << "): ";
        std::cin >> x;
        std::cout << "Enter y coordinate (0 < y < " << max_y << "): ";
        std::cin >> y;

        if (x > 0 && x < max_x && y > 0 && y < max_y) {
            x += body_x_diff + (int) body.get_r_foot().get_line().get_end().get_x();
            y += OBJ_RADIUS;
            break;
        } else {
            std::cout << "Invalid coordinates. Please try again.\n";
        }
    }

    sf::RenderWindow window(sf::VideoMode(X_PIXELS, Y_PIXELS), "Line Example");

    float ground_y = 9 * Y_PIXELS / 10;


    Body_drawer bd(window, ground_y);
    
    Obj obj(Point((float)x, (float)y), OBJ_RADIUS, ground_y);

    Animate animator(body);

    std::unique_ptr<Movement_iterator> walking_movement = animator.step_forward_iterator();
    std::unique_ptr<Movement_iterator> stand_upright_movement = animator.stand_upright_iterator();


    float arm_reach = HUMERUS_LENGTH + RADIUS_LENGTH + MIDDLE_FINGER_LENGTH;

    float x_diff = obj.get_center().get_x() - arm_reach - body.get_r_clavicle().get_line().get_end().get_x();

    Point future_shoulder = Point(body.get_r_clavicle().get_line().get_end().get_x() + x_diff, body.get_r_clavicle().get_line().get_end().get_y());
    Point future_hip = Point(body.get_spine().get_line().get_start().get_x() + x_diff, body.get_spine().get_line().get_start().get_y());

    float spine_angle = get_spine_rotation_angle(future_hip, future_shoulder, obj.get_center(), arm_reach);

    float arm_angle = get_arm_rotation_angle(future_shoulder, future_hip, obj.get_center(), arm_reach, spine_angle - M_PI_2);

    Parallel_movement* grabbing_movement(animator.make_grab_movement(arm_angle, spine_angle));

    std::unique_ptr<Movement_iterator> grab = grabbing_movement->initiate();

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

        if (obj.get_center().get_x() - spine.get_start().get_x() > arm_reach + CLAVICLE_LENGTH) {
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

    delete grabbing_movement;
    grabbing_movement = nullptr;
    

    return 0;
}