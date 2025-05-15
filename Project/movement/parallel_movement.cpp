#include "parallel_movement.h"

Parallel_movement::Parallel_movement(Body& body): Movement_cluster(body), current_step_index(0) {}

bool Parallel_movement::make_step() {
    int finished_movements = 0;
    for (Movement_iterator* movement : movements) {
        finished_movements += !movement->make_step();
    }

    if (finished_movements == movements.size()) {
        return false;
    }

    return true;
}