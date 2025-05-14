#include "movement_cluster.h"

Movement_cluster::Movement_cluster(Body& body): Movement_iterator(body) {}

void Movement_cluster::add_movement(Movement_iterator* movement) {
    movements.push_back(movement);
}

void Movement_cluster::add_movements(std::vector<Movement_iterator*> movements) {
    for (auto movement : movements) {
        add_movement(movement);
    }
}