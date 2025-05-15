#pragma once

#include "../body.h"
#include "movement.h"
#include "movement_iterator.h"
#include "basic_movement_iterator.h"


class Basic_movement: public Movement {
public:
    Basic_movement(
        Body& body,
        float target,
        int steps,
        void (*callback)(Body& body, float target),
        float (*current_state)(Body& body) = nullptr
    );
    Movement_iterator initiate() override;
    // bool make_step() override;

private:
    // Body& body;
    int steps;
    // int completed_steps;
    float target;
    void (*callback)(Body& body, float target);
    float (*current_state)(Body& body);
    // float d_femur;
    // float d_tibia;
};