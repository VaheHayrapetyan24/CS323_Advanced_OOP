#include "head.h"
#include "body_visitor.h"

Head::Head(Point& anchor, Point& center): Part(anchor), center(center) {}

void Head::shift(float dx, float dy) {
    anchor.shift(dx, dy);
    center.shift(dx, dy);
}

void Head::rotate_around(float x, float y, float phi) {
    anchor.rotate_around(x, y, phi);
    center.rotate_around(x, y, phi);
}

float Head::get_radius() {
    return anchor.dist(center);
}

void Head::accept(Body_visitor* visitor) {
    visitor->visit(this);
}

Point Head::get_center() {
    return center;
}