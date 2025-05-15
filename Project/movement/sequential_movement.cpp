#include "sequential_movement.h"


Sequential_movement::Sequential_movement(Body& body): Movement_cluster(body), current_movement_index(0) {
    // std::cout << "Initializing Sequential_movement with completed_steps = 0" << std::endl;
}
bool Sequential_movement::make_step() {
    // printf("%d\n", current_movement_index);
    if (current_movement_index >= movements.size()) {
        return false;
    }

    Movement_iterator* current_movement = movements[current_movement_index];


    // printf("trying current movement\n");
    if (!current_movement->make_step()) {
        current_movement_index++;
        return make_step();
    }
    // printf("finished current movement\n");

    return true;
}