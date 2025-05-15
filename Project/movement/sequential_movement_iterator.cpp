#include "sequential_movement_iterator.h"
#include "sequential_movement.h"

Sequential_movement_iterator::Sequential_movement_iterator(Body& body, std::vector<Movement*> &movements)
    : Movement_iterator(body), current_movement_index(0) {
    for (Movement* movement : movements) 
        this->movements.push_back(movement->initiate());
}

bool Sequential_movement_iterator::make_step() {
    if (current_movement_index >= movements.size()) {
        return false;
    }

    Movement_iterator& current_movement = movements[current_movement_index];

    if (!current_movement.make_step()) {
        current_movement_index++;
        return make_step();
    }

    return true;
}