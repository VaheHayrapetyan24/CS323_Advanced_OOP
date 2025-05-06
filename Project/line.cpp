#include "point.h"
#include "line.h"


Line::Line(Point& p1, Point& p2): start{p1}, end{p2} {}

Point& Line::get_start() {
    return start;
}


Point& Line::get_end() {
    return end;
}

float Line::slope() {
    return start.dir(end);
}

float Line::length() {
    return start.dist(end);
}

void Line::shift(float dx, float dy) {
    start.shift(dx, dy);
    end.shift(dx, dy);
}

void Line::rotate(float da) {
    float ang = slope() + da, len = length();
    end.shift(
        start.get_x() + len * cos(ang) - end.get_x(), 
        start.get_y() + len * sin(ang) - end.get_y());
}

void Line::rotate_around(float x, float y, float phi) {
    start.rotate_around(x, y, phi);
    end.rotate_around(x, y, phi);
}