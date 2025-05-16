#pragma once

#include <SFML/Graphics.hpp>
#include "point.h"


class Box {
public:
    Box(Point l_b_corner, float width, float height, float dy);
    void draw(sf::RenderWindow& window);
    Point& get_l_b_corner();
private:
    Point l_b_corner;
    float width;
    float height;
    float dy;
};