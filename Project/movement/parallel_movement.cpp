#include "parallel_movement.h"
#include "parallel_movement_iterator.h"

std::unique_ptr<Movement_iterator> Parallel_movement::initiate() {
    return std::make_unique<Parallel_movement_iterator>(movements);
}