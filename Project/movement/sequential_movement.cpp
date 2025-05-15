#include "sequential_movement.h"


Sequential_movement::Sequential_movement(Body& body): Movement_cluster(body) {}


Movement_iterator Sequential_movement::initiate() {
    return Sequential_movement_iterator(body, movements);
}