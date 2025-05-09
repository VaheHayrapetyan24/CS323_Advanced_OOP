#include <vector>
#include "point.h"

class Part {
    public:
        Part(Point& anchor);
        virtual void shift(float dx, float dy) = 0;
        virtual void rotate_around(float x, float y, float phi) = 0;
        virtual void rotate(float phi); // this is always around anchor
        std::vector<Part*>* get_subparts();
    protected:
        Point& anchor;
        std::vector<Part*>* subparts;
};