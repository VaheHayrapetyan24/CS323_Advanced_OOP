#include "segment_illustrate.h"
#include <iostream> 

std::function<void(Part*)> segment_illustrate(sf::RenderWindow& window) {
    std::function<void(Part*)> recurse = [&window, &recurse](Part* s) -> void {
        sf::Vertex line[] =
        {
            // TODO: think about solution
            // sf::Vertex(sf::Vector2f(((Body_segment*)s)->get_line().get_start().get_x(), ((Body_segment*)s)->get_line().get_start().get_y()), sf::Color::Red),
            // sf::Vertex(sf::Vector2f(((Body_segment*)s)->get_line().get_end().get_x(), ((Body_segment*)s)->get_line().get_end().get_y()), sf::Color::Red)
        };

        window.draw(line, 2, sf::Lines);


        if (s->get_subparts() == nullptr) {
            return;
        }

        for (Part* subseg : *(s -> get_subparts())) {
            recurse(subseg);
        }
    };

    return recurse;
}
