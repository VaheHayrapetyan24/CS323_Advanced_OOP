#pragma once
#include "part.h"
#include "point.h"

class Body_visitor;

class Head: public Part {
    public:
        Head(Point& anchor, Point& center);
        void shift(float dx, float dy) override;
        void rotate_around(float x, float y, float phi, bool f = true) override;
        void accept(Body_visitor* visitor) override;
        float get_radius();
        Point get_center();
    private:
        Point& center;
};




