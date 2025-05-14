#include "movement.h"


Movement::Movement(
    Body& body,
    float target,
    int steps,
    void (*callback)(Body& body, float target)
): Movement_iterator(body), steps(steps), completed_steps(0), target(target), callback(callback) {
    // std::cout << "Initializing Movement with completed_steps = 0" << std::endl;
}

bool Movement::make_step() {
    if (completed_steps >= steps) {
        return false;
    }

    // printf("trying callback %f\n", (float)++completed_steps);
    callback(body, target / steps);
    completed_steps++;
    // printf("finished callback\n");
    return true;
}

