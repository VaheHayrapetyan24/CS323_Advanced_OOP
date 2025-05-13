#include "body_segment.h"
#include "line.h"
#include "body_visitor.h"
#include <iostream>

Body_segment::Body_segment(Point& anchor, Point& end): Part(anchor), anchor_line(anchor, end) {}

Body_segment::Body_segment(Line& al): Body_segment(al.get_start(), al.get_end()) {}

void Body_segment::shift(float dx, float dy) {
    anchor_line.shift(dx, dy);
    if (subparts.size() == 0) {
        return;
    }
    for (Part* subseg : subparts) {
        subseg->shift(dx, dy);
    }
}

void Body_segment::rotate_around(float x, float y, float phi) {
    anchor_line.rotate_around(x, y, phi);
    if (subparts.size() == 0) {
        return;
    }
    for (Part* subseg : subparts) {
        subseg->rotate_around(x, y, phi);
    }
}

void Body_segment::rotate(float phi) {
    anchor_line.rotate_around(anchor.get_x(), anchor.get_y(), phi);
    Part::rotate(phi);
}

float Body_segment::slope() {
    return anchor_line.slope();
}

Line Body_segment::get_line() {
    return anchor_line; // TODO: copy?
}

void Body_segment::accept(Body_visitor* visitor) {
    visitor->visit(this);
}
