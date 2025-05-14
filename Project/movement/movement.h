#pragma once

#include "../body.h"
#include "movement_iterator.h"


class Movement: public Movement_iterator {
public:
    Movement(
        Body& body,
        float target,
        int steps,
        void (*callback)(Body& body, float target)
    );
    bool make_step() override;

private:
    // Body& body;
    int steps;
    int completed_steps;
    float target;
    void (*callback)(Body& body, float target);
    // float d_femur;
    // float d_tibia;
};