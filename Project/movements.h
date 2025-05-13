#include <iostream>
#include <cmath> // For M_PI

#include "body.h"

class MovementIterator {
public:
    MovementIterator(Body& body, int steps);
    bool make_step();

private:
    Body& body;
    int steps;
    int completed_steps;
    float femur_angle;
    float tibia_angle;
    // float d_femur;
    // float d_tibia;
};