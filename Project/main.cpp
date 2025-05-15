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


    Movement a(body, M_PI, 1000, [](Body& body, float target) {
        body.get_l_femur().rotate(target);
    });
    Movement b(body, -M_PI / 2, 100, [](Body& body, float target) {
        body.get_l_tibia().rotate(target);
    });

    Parallel_movement stepper(body);
    stepper.add_movement(&a);
    stepper.add_movement(&b);

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
