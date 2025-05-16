#pragma once

#include "../body.h"
#include "movement.h"
#include "movement_iterator.h"
#include "basic_movement_iterator.h"
#include <functional> // For std::function

class Basic_movement : public Movement {
public:
    Basic_movement(
        Body& body,
        float target,
        int steps,
        std::function<void(Body&, float)> callback,
        std::function<float(Body&)> current_state = nullptr
    );

    std::unique_ptr<Movement_iterator> initiate() override;

private:
    int steps;
    float target;
    std::function<void(Body&, float)> callback;
    std::function<float(Body&)> current_state;
};