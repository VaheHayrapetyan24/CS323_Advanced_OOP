#include "parallel_movement_iterator.h"
#include "parallel_movement.h"

Parallel_movement_iterator::Parallel_movement_iterator(std::vector<Movement*> &movements) {
        for (Movement* movement : movements) 
            this->movements.push_back(movement->initiate());
}

bool Parallel_movement_iterator::make_step() {
    int finished_movements = 0;
    for (std::unique_ptr<Movement_iterator> &movement : movements) {
        finished_movements += !movement->make_step();
    }

    if (finished_movements == movements.size()) {
        return false;
    }

    return true;
}