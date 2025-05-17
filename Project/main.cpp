#include <SFML/Graphics.hpp>
#include <iostream>

#include "body_segment.h"
#include "point.h"
#include "line.h"
#include "body.h"
#include "body_visitor.h"
#include "obj.h"

// #include "movement/movement_iterator.h"
// #include "movement/basic_movement.h"
// #include "movement/sequential_movement.h"
#include "movement/parallel_movement.h"
#include "animate.h"

bool is_point_in_circle(Point p, Point c, float r) {
    
    float dx = p.get_x() - c.get_x();
    float dy = p.get_y() - c.get_y();
    std::cout << "Point: (" << p.get_x() << ", " << p.get_y() << "), "
              << "Circle Center: (" << c.get_x() << ", " << c.get_y() << "), "
              << "Radius: " << r << ", "
            << "Distance squared: " << (dx * dx + dy * dy) << ", "
              << "Result: " << ((dx * dx + dy * dy) <= (r * r)) << std::endl;
    return (dx * dx + dy * dy) <= (r * r);
}

float get_spine_rotation_angle(Point& anchor, Point& clavicle, Point& obj_center, float arm_reach) {
    printf("get_spine_rotation_angle\n");
    float slope = anchor.dir(clavicle);
    printf("slope %f\n", slope);
    float dist = anchor.dist(clavicle);
    printf("dist %f\n", dist);
    for (; slope > -M_PI_2; slope -= 0.1) {
        printf("angle %f\n", slope);
        float x = anchor.get_x() + dist * cos(slope);
        float y = anchor.get_y() + dist * sin(slope);
        if (is_point_in_circle(Point(x, y), obj_center, arm_reach)) {
            return slope;
        }
    }
    return 0;

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

    Parallel_movement parallel_movement(body);
    std::unique_ptr<Movement_iterator> grab;


    // if (obj.get_center().get_y() > body.get_l_femur().get_line().get_start().get_y()) {
    float arm_reach = body.get_r_humerus().get_line().length() + body.get_r_radius().get_line().length();

    float x_diff = obj.get_center().get_x() - body.get_spine().get_line().length() - body.get_spine().get_line().get_start().get_x();

    Point future_point = Point(obj.get_center().get_x() - body.get_spine().get_line().length() + body.get_l_clavicle().get_line().length(), body.get_r_clavicle().get_line().get_end().get_y());

    // Point c = obj.get_center();

    if (is_point_in_circle(
        future_point,
        obj.get_center(),
        arm_reach
    )) {
        printf(" in the circleeeee\n");
        float dir = future_point.dir(obj.get_center());
        parallel_movement.add_movement(std::make_unique<Basic_movement>(
            body, dir, 400,
            [](Body& body, float target) { body.get_r_humerus().rotate(target); },
            [](Body& body) { return body.get_r_humerus().slope(); }
        ).release());
        parallel_movement.add_movement(std::make_unique<Basic_movement>(
            body, dir, 400,
            [](Body& body, float target) { body.get_r_radius().rotate(target); },
            [](Body& body) { return body.get_r_radius().slope(); }
        ).release());
        // grab = parallel_movement.initiate();

        // grab = std::make_unique<Basic_movement>(body, 0, 0, [](Body& body, float target) {}, [](Body& body) { return 0; });
    } else {
        printf("elseseeeeee\n");
        Point future_shoulder = Point(body.get_r_clavicle().get_line().get_end().get_x() + x_diff, body.get_r_clavicle().get_line().get_end().get_y());
        Point future_hip = Point(body.get_spine().get_line().get_start().get_x() + x_diff, body.get_spine().get_line().get_start().get_y());
        printf("future shoulder %f, %f\n", future_shoulder.get_x(), future_shoulder.get_y());
        printf("future hip %f, %f\n", future_hip.get_x(), future_hip.get_y());
        float angle = get_spine_rotation_angle(future_hip, future_shoulder, obj.get_center(), arm_reach);
        printf("angleee %f\n", angle);
        parallel_movement.add_movement(std::make_unique<Basic_movement>(
            body, angle, 400,
            [](Body& body, float target) { 
                printf("rotate spine %f\n", target);
                body.get_spine().rotate(target);
            },
            [](Body& body) { return body.get_spine().slope(); }
        ).release());
        printf("movement added\n");
        


        // grab = std::make_unique<Basic_movement>(body, 0, 0, [](Body& body, float target) {}, [](Body& body) { return 0; });
    }
    grab = parallel_movement.initiate();

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

        if (obj.get_center().get_x() - spine.get_start().get_x() > spine.length()) {
            if (!walking_movement->make_step()) {
                walking_movement = animator.step_forward_iterator();
            }
        } else {
            if (!stand_upright_movement->make_step()) {
                // here check if obj is upper than hip

                if (!grab->make_step()) {

                }
                
            }
        }

        obj.draw(window);
        window.display();
    }

    

    return 0;
}



// #include <SFML/Graphics.hpp>

// #include "body_segment.h"
// #include "point.h"
// #include "line.h"
// #include "body.h"
// #include "body_visitor.h"

// // #include "segment_illustrate.h"

// int main()
// {
//     sf::RenderWindow window(sf::VideoMode(2000, 2000), "Line Example");

//     // Point p1(50.f, 50.f), p2(350.f,350.f);
//     // Line l(p1, p2);
//     // Point p3(50.f, 350.f), p4(350.f, 50.f);
//     // Line l2(p2, p3);
//     // std::vector<Part*> subsegments;
//     // Body_segment bs2(l2);
//     // subsegments.push_back(&bs2);

//     // Body_segment bs(l);
//     // auto fn = segment_illustrate(window);

//     Body body(300, 0);
//     Body_drawer bd(window, 1000);

//     int i = 0;
//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//                 window.close();
//         }

//         window.clear();

//         bd.visit(&body);

//         if (i % 10 == 0){
//             // body.get_l_femur().rotate(0.01f);
//             // body.get_r_femur().rotate(-0.01f);
//             body.get_spine().rotate(0.1f);
//         }
//         ++i;



        
        

//         // if (i % 10 == 0) {
//             // bs.shift(1, 1);
//             // bs.rotate_around(p1.get_x(), p1.get_y(), 0.1f);
//         // }

//         window.display();
//     }

    

//     return 0;
// }