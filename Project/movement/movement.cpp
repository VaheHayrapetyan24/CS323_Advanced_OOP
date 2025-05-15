#include "movement.h"


Movement::Movement(
    Body& body,
    float target,
    int steps,
    void (*callback)(Body& body, float target)
): Movement_iterator(body), steps(steps), completed_steps(0), target(target), callback(callback) {}

bool Movement::make_step() {
    if (completed_steps >= steps) {
        return false;
    }

    callback(body, target / steps);
    completed_steps++;
    return true;
}

