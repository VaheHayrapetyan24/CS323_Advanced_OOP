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
                // stand_upright_movement = animator.stand_upright_iterator();
            }
            // here do the other movement
        }

        obj.draw(window);
        window.display();
    }

    

    return 0;
}
