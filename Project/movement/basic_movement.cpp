#include "basic_movement.h"


Basic_movement::Basic_movement(
    Body& body,
    float target,
    int steps,
    std::function<void(Body&, float)> callback,
    std::function<float(Body&)> current_state 
): Movement(body), steps(steps), target(target), callback(callback), current_state(current_state) {}

std::unique_ptr<Movement_iterator> Basic_movement::initiate() {
    return std::make_unique<Basic_movement_iterator>(body, target, steps, callback, current_state);
}

