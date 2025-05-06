#pragma once
#include "point.h"
#include "line.h"
#include <vector>

class Part {
    public: 
        virtual void shift(float dx, float dy) = 0;
    protected:
        Point anchor;
};

// class Segment: public Part {
//     public:
//         Segment();
//         Segment(std::vector<Segment>* subsegments);
//     protected:
//         std::vector<Segment>* subsegments;
// };

class Body_segment: public Part {
    public:
        Body_segment(Line al);
        Body_segment(Line al, std::vector<Body_segment*>* subseg);
        void shift(float dx, float dy) override;
        void rotate_around(float x, float y, float phi);
        Line get_line();
        std::vector<Body_segment*>* get_subsegments();
    private:
        std::vector<Body_segment*>* subsegments;
        Line anchor_line;
};