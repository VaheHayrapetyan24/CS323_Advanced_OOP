#include "parallel_movement.h"
#include "parallel_movement_iterator.h"

Parallel_movement::Parallel_movement(Body& body): Movement_cluster(body) {}

Movement_iterator Parallel_movement::initiate() {
    return Parallel_movement_iterator(body, movements);
}