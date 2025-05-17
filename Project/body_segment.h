#pragma once
#include "point.h"
#include "line.h"
#include "part.h"
#include <vector>

class Body_visitor;

class Body_segment: public Part {
    public:
        Body_segment(Line& al);
        Body_segment(Point& anchor, Point& end);
        void shift(float dx, float dy, bool f = true) override;
        void rotate_around(float x, float y, float phi, bool f = true) override;
        void rotate(float phi) override;
        void accept(Body_visitor* visitor) override;
        float slope();
        Line& get_line();
    private:
        Line anchor_line;
};