#include "movement.h"


Movement::Movement(
    Body& body,
    float target,
    int steps,
    void (*callback)(Body& body, float target),
    float (*current_state)(Body& body)
): Movement_iterator(body), steps(steps), completed_steps(0), target(target), callback(callback), current_state(current_state) {}

bool Movement::make_step() {
    if (completed_steps >= steps) {
        return false;
    }

    if (current_state != nullptr) {
        float current = current_state(body);
        callback(body, (target - current) / (steps - completed_steps ));
    } else {
        callback(body, target / steps);
    }

    completed_steps++;
    return true;
}

