#include "part.h"


Part::Part(Point& anchor): anchor(anchor) {
    subparts = nullptr;
}

void Part::rotate(float phi) {
    if (subparts == nullptr) {
        return;
    }

    for (Part* subpart : *subparts) {
        subpart->rotate_around(anchor.get_x(), anchor.get_y(), phi);
    }
}



std::vector<Part*>* Part::get_subparts() {
    return subparts;
}