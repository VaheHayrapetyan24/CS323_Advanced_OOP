#include "body_segment.h"
#include <iostream>

Body_segment::Body_segment(Line& al): Part(al.get_start()), anchor_line(al) {
    subparts = nullptr;
}

Body_segment::Body_segment(Line& al, std::vector<Part*>* subseg): Part(al.get_start()), anchor_line(al) {
    subparts = subseg;
    anchor = al.get_start();
}

void Body_segment::shift(float dx, float dy) {
    anchor_line.shift(dx, dy);
    if (subparts == nullptr) {
        return;
    }
    for (Part* subseg : *subparts) {
        subseg->shift(dx, dy);
    }
}

void Body_segment::rotate_around(float x, float y, float phi) {
    anchor_line.rotate_around(x, y, phi);
    if (subparts == nullptr) {
        return;
    }
    for (Part* subseg : *subparts) {
        subseg->rotate_around(x, y, phi);
    }
}

void Body_segment::rotate(float phi) {
    anchor_line.rotate_around(anchor.get_x(), anchor.get_y(), phi);
    Part::rotate(phi);
}

Line& Body_segment::get_line() {
    return anchor_line;
}
