#pragma once

#include <SFML/Graphics.hpp>
#include "point.h"
#include "body.h"

#define OBJ_RADIUS 50 * SCALE

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