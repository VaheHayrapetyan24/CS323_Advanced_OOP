#include "part.h"


Part::Part(Point& anchor): anchor(anchor) {}

void Part::rotate(float phi) {
    if (subparts.size() == 0) {
        return;
    }

    for (Part* subpart : subparts) {
        subpart->rotate_around(anchor.get_x(), anchor.get_y(), phi);
    }
}

void Part::add_subpart(Part* subpart) {
    subparts.push_back(subpart);
}

std::vector<Part*>* Part::get_subparts() {
    return &subparts;
}