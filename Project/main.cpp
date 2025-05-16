#include <SFML/Graphics.hpp>

#include "body_segment.h"
#include "point.h"
#include "line.h"
#include "body.h"
#include "body_visitor.h"
#include "box.h"

// #include "movement/movement_iterator.h"
// #include "movement/basic_movement.h"
// #include "movement/sequential_movement.h"
#include "movement/parallel_movement.h"
#include "animate.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(2000, 2000), "Line Example");

    Body body(500, 0);
    Body_drawer bd(window, 1000);

    int i = 0;

    Box box(Point(1000, 0), 200, 100, 1000);
    Animate animator(body);

    std::unique_ptr<Movement_iterator> walking_movement = animator.step_forward_iterator();
    std::unique_ptr<Movement_iterator> stand_upright_movement = animator.stand_upright_iterator();
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

        if (box.get_l_b_corner().get_x() - spine.get_start().get_x() > spine.length()) {
            if (!walking_movement->make_step()) {
                walking_movement = animator.step_forward_iterator();
            }
        } else {
            if (!stand_upright_movement->make_step()) {
                // stand_upright_movement = animator.stand_upright_iterator();
            }
            // here do the other movement
        }

        box.draw(window);
        window.display();
    }

    

    return 0;
}
