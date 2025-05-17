#include "body_visitor.h"
#include "body_segment.h"
#include "head.h"
#include "body.h" 

void Body_drawer::visit(class Body_segment* body_segment) {
    sf::Vertex line[] =
    {
        sf::Vertex(sf::Vector2f(body_segment->get_line().get_start().get_x(), dy - body_segment->get_line().get_start().get_y()), sf::Color::Red),
        sf::Vertex(sf::Vector2f(body_segment->get_line().get_end().get_x(), dy - body_segment->get_line().get_end().get_y()), sf::Color::Red)
    };

    window.draw(line, 2, sf::Lines);

    if (body_segment->get_subparts() == nullptr) {
        return;
    }

    for (Part* subseg : *(body_segment->get_subparts())) {
        subseg->accept(this);
    }
}

void Body_drawer::visit(class Head* head) {
    float radius = head->get_radius();
    sf::CircleShape circle(radius);
    circle.setPosition(head->get_center().get_x() - radius, dy - head->get_center().get_y() - radius);
    circle.setFillColor(sf::Color::Green);
    window.draw(circle);
}

void Body_drawer::visit(class Body* body) {
    body->get_l_femur().accept(this);
    body->get_r_femur().accept(this);
    body->get_spine().accept(this);
}