#include "segment.h"

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

Line Body_segment::get_line() {
    return anchor_line;
}

std::vector<Body_segment*>* Body_segment::get_subsegments() {
    return subsegments;
}