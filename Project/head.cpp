#include "head.h"

Head::Head(Point& anchor, Point& center): Part(anchor), center(center) {
    subparts = nullptr;
}

void Head::shift(float dx, float dy) {
    anchor.shift(dx, dy);
}

void Head::rotate_around(float x, float y, float phi) {
    anchor.rotate_around(x, y, phi);
}

float Head::get_radius() {
    return anchor.dist(center);
}