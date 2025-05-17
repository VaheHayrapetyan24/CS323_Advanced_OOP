#pragma once
#include <vector>
#include "point.h"

class Body_visitor;

class Part {
    public:
        Part(Point& anchor);
        virtual void shift(float dx, float dy, bool f = true) = 0;
        virtual void rotate_around(float x, float y, float phi, bool f = true) = 0;
        virtual void rotate(float phi); // this is always around anchor
        virtual void accept(Body_visitor* visitor) = 0;
        void add_subpart(Part* subpart);
        std::vector<Part*>* get_subparts();
    protected:
        Point& anchor;
        std::vector<Part*> subparts;
};