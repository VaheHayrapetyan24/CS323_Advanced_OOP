#include "box.h"


Box::Box(Point l_b_corner, float width, float height, float dy) : l_b_corner(l_b_corner), width(width), height(height), dy(dy) {}
void Box::draw(sf::RenderWindow& window) {

    sf::RectangleShape rectangle(sf::Vector2f(width, height));
    rectangle.setPosition(l_b_corner.get_x(), dy - l_b_corner.get_y() - height);

    window.draw(rectangle);
}

Point& Box::get_l_b_corner() {
    return l_b_corner;
}