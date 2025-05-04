#include "segment.h"

Segment::Segment(std::vector<Segment>* subsegments) : subsegments(subsegments) {}

Segment::Segment() : subsegments() {}



Body_segment::Body_segment(Line al): anchor_line(al) {}

Body_segment::Body_segment(Line al, std::vector<Segment>* subseg)
    : Segment(subseg), anchor_line(al) {}

void Body_segment::shift(float dx, float dy) {
    anchor.shift(dx, dy);
    anchor_line.shift(dx, dy);
    for (Segment& subseg : *subsegments) {
        subseg.shift(dx, dy);
    }
}
