#include "sequential_movement.h"


Sequential_movement::Sequential_movement(Body& body): Movement_cluster(body) {}


std::unique_ptr<Movement_iterator> Sequential_movement::initiate() {
    printf("sequential_movement::initiate\n");
    return std::make_unique<Sequential_movement_iterator>(body, movements);
}