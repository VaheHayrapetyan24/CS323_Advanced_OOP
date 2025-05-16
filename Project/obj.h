#pragma once

#include <SFML/Graphics.hpp>
#include "point.h"


class Obj {
public:
    Obj(Point center, float radius, float dy);
    void draw(sf::RenderWindow& window);
    Point& get_center();
private:
    Point center;
    float radius;
    float dy;
};