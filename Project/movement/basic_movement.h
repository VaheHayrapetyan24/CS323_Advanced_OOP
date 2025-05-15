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
    std::unique_ptr<Movement_iterator> initiate() override;
private:
    int steps;
    float target;
    void (*callback)(Body& body, float target);
    float (*current_state)(Body& body);
};