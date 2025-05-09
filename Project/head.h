#include "part.h"
#include "point.h"

class Head: public Part {
    public:
        Head(Point& anchor, Point& center);
        void shift(float dx, float dy) override;
        void rotate_around(float x, float y, float phi) override;
        float get_radius();
    private:
        Point& center;
};




