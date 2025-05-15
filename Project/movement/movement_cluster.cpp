#include "movement_cluster.h"

Movement_cluster::Movement_cluster(Body& body): Movement(body) {}

void Movement_cluster::add_movement(Movement* movement) {
    movements.push_back(movement);
}

void Movement_cluster::add_movements(std::vector<Movement*> movements) {
    for (auto movement : movements) {
        add_movement(movement);
    }
}