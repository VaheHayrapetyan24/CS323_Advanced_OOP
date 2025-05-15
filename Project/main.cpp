#include <SFML/Graphics.hpp>

#include "body_segment.h"
#include "point.h"
#include "line.h"
#include "body.h"
#include "body_visitor.h"

#include "movement/movement_iterator.h"
#include "movement/movement.h"
#include "movement/sequential_movement.h"
#include "movement/parallel_movement.h"
// #include "segment_illustrate.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(2000, 2000), "Line Example");

    Body body(500, 0);
    Body_drawer bd(window, 1000);

    int i = 0;


    Movement a(body, -  M_PI / 8, 300, [](Body& body, float target) {
        body.get_l_femur().rotate(target);
    }, [](Body& body) {
        return body.get_l_femur().slope();
    });
    Movement b(body, - 3 * M_PI / 8, 250, [](Body& body, float target) {
        body.get_l_tibia().rotate(target);
    });

    Parallel_movement stepper(body);
    stepper.add_movement(&a);
    stepper.add_movement(&b);


    // Movement r_f_up(body, M_PI / 2, 200, [](Body& body, float target) {
    //     body.get_r_femur().rotate(target);
    // });
    // Movement r_t_up(body, -M_PI/2, 200, [](Body& body, float target) {
    //     body.get_r_tibia().rotate(target);
    // });
    // Parallel_movement stepper2(body);
    // stepper2.add_movement(&r_f_up);
    // stepper2.add_movement(&r_t_up);

    // Sequential_movement stepper3(body);
    // stepper3.add_movement(&stepper);
    // stepper3.add_movement(&stepper2);

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

        

        if (!stepper.make_step()) {
            break;
        }

        window.display();
    }

    

    return 0;
}
