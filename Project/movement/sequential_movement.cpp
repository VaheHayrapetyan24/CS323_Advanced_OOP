#include "sequential_movement.h"


std::unique_ptr<Movement_iterator> Sequential_movement::initiate() {
    return std::make_unique<Sequential_movement_iterator>(movements);
}