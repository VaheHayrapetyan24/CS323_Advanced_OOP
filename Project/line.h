
#pragma once
#include "point.h"

class Line {
public:
    Line(Point& p1, Point& p2);
    Point& get_start();
    Point& get_end();
    float slope();
    float length();
    void shift(float dx, float dy);
    void rotate(float phi);
    void rotate_around(float dx, float dy, float phi);
private:
    Point start, end;
};