#include <SFML/Graphics.hpp>

#include "body_segment.h"
#include "point.h"
#include "line.h"
#include "body.h"
#include "body_visitor.h"

#include "movement/movement_iterator.h"
#include "movement/movement.h"
#include "movement/sequential_movement.h"
// #include "segment_illustrate.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(2000, 2000), "Line Example");

    // Point p1(50.f, 50.f), p2(350.f,350.f);
    // Line l(p1, p2);
    // Point p3(50.f, 350.f), p4(350.f, 50.f);
    // Line l2(p2, p3);
    // std::vector<Part*> subsegments;
    // Body_segment bs2(l2);
    // subsegments.push_back(&bs2);

    // Body_segment bs(l);
    // auto fn = segment_illustrate(window);

    Body body(500, 0);
    Body_drawer bd(window, 1000);

    int i = 0;


    Movement a(body, M_PI, 1000, [](Body& body, float target) {
        // printf("target %f\n", target);
        // printf("moving femur x %f y %f\n", body.get_l_femur().get_line().get_end().get_x(), body.get_l_femur().get_line().get_end().get_y());
        body.get_l_femur().rotate(target);
        // printf("moved femur x %f y %f\n", body.get_l_femur().get_line().get_end().get_x(), body.get_l_femur().get_line().get_end().get_y());
    });
    Movement b(body, -M_PI / 2, 100, [](Body& body, float target) {
        body.get_l_tibia().rotate(target);
    });
    // printf("before stepper\n");
    Sequential_movement stepper(body);
    // printf("adding movement a\n");
    stepper.add_movement(&a);
    // printf("adding movement b\n");
    stepper.add_movement(&b);
    // printf("mmovements are added\n");
    // MovementIterator stepper(body, 100);
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

        

        

        // body.get_l_femur().rotate(0.01f);
        // body.get_r_femur().rotate(-0.01f);
        // body.get_spine().rotate(0.01f);

        // printf("stepping\n");
        if (!stepper.make_step()) {
            // std::cout << "Step " << i << std::endl;
            // stepper();
            break;
        }
        // printf("stepped\n");
        

        // if (i % 10 == 0) {
            // bs.shift(1, 1);
            // bs.rotate_around(p1.get_x(), p1.get_y(), 0.1f);
        // }

        window.display();
    }

    

    return 0;
}
