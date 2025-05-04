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

class Segment: public Part {
    public:
        Segment();
        Segment(std::vector<Segment>* subsegments);
    protected:
        std::vector<Segment>* subsegments;
};

class Body_segment: public Segment {
    public:
        Body_segment(Line al);
        Body_segment(Line al, std::vector<Segment>* subseg);
        void shift(float dx, float dy) override;
    private:
        Line anchor_line;
};