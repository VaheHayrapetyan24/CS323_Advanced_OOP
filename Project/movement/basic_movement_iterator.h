#pragma once

#include "movement_iterator.h"

class Basic_movement;

class Basic_movement_iterator: public Movement_iterator {
friend class Basic_movement;
public:
    bool make_step() override;
private:
    Basic_movement_iterator(Body& body, float target, int steps, void (*callback)(Body& body, float target), float (*current_state)(Body& body) = nullptr);
    int steps;
    int completed_steps;
    float target;
    void (*callback)(Body& body, float target);
    float (*current_state)(Body& body);
};