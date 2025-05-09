#pragma once
#include "point.h"
#include "line.h"
#include "part.h"
#include <vector>

class Body_segment: public Part {
    public:
        Body_segment(Line& al);
        Body_segment(Point& anchor, Point& end);
        Body_segment(Point& anchor, Point& end, std::vector<Part*>* subseg);
        Body_segment(Line& al, std::vector<Part*>* subseg);
        void shift(float dx, float dy) override;
        void rotate_around(float x, float y, float phi) override;
        void rotate(float phi) override;
        Line& get_line();
    private:
        Line& anchor_line;
};