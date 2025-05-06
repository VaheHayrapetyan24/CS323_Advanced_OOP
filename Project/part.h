#include "point.h"

class Part {
    public: 
        virtual void shift(float dx, float dy) = 0;
    protected:
        Point anchor;
};