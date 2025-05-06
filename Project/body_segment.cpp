#include "body_segment.h"
#include <iostream>

Body_segment::Body_segment(Line al): anchor_line(al) {}

Body_segment::Body_segment(Line al, std::vector<Body_segment*>* subseg)
    : subsegments(subseg), anchor_line(al) {}

void Body_segment::shift(float dx, float dy) {
    anchor_line.shift(dx, dy);
    if (subsegments == nullptr) {
        return;
    }
    for (Body_segment* subseg : *subsegments) {
        subseg->shift(dx, dy);
    }
}

void Body_segment::rotate_around(float x, float y, float phi) {
    anchor_line.get_start().rotate_around(x, y, phi);
    anchor_line.get_end().rotate_around(x, y, phi);
    if (subsegments == nullptr) {
        return;
    }
    for (Body_segment* subseg : *subsegments) {
        subseg->rotate_around(x, y, phi);
    }
}

Line Body_segment::get_line() {
    return anchor_line;
}

std::vector<Body_segment*>* Body_segment::get_subsegments() {
    return subsegments;
}