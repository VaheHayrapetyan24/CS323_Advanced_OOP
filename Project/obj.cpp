#include "obj.h"

Obj::Obj(Point center, float radius, float dy) : center(center), radius(radius), dy(dy) {}

void Obj::draw(sf::RenderWindow& window) {
    sf::CircleShape circle(radius);
    circle.setPosition(center.get_x() - radius, dy - center.get_y() - radius);
    circle.setFillColor(sf::Color::Yellow);
    window.draw(circle);
}

Point& Obj::get_center() {
    return center;
}