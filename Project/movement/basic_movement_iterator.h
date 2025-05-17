#pragma once

#include "movement_iterator.h"
#include <functional>
class Basic_movement;

class Basic_movement_iterator : public Movement_iterator {
    friend class Basic_movement;
public:
    bool make_step() override;

    Basic_movement_iterator(
        Body& body,
        float target,
        int steps,
        std::function<void(Body&, float)> callback,
        std::function<float(Body&)> current_state = nullptr
    );

private:
    Body& body;
    int steps;
    int completed_steps;
    float target;
    std::function<void(Body&, float)> callback;
    std::function<float(Body&)> current_state;
};