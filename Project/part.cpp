#include "part.h"


void Part::rotate(float phi) {
    if (subparts == nullptr) {
        return;
    }

    for (Part* subpart : *subparts) {
        subpart->rotate_around(anchor.get_x(), anchor.get_y(), phi);
    }
}

