#include "segment_illustrate.h"
#include <iostream> 

std::function<void(Body_segment*)> segment_illustrate(sf::RenderWindow& window) {
    std::function<void(Body_segment*)> recurse = [&window, &recurse](Body_segment* s) -> void {
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(s->get_line().get_start().get_x(), s->get_line().get_start().get_y()), sf::Color::Red),
            sf::Vertex(sf::Vector2f(s->get_line().get_end().get_x(), s->get_line().get_end().get_y()), sf::Color::Red)
        };

        window.draw(line, 2, sf::Lines);


        if (s->get_subsegments() == nullptr) {
            return;
        }

        for (Body_segment* subseg : *(s -> get_subsegments())) {
            recurse(subseg);
        }
    };

    return recurse;
}
