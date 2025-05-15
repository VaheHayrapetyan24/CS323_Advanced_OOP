#pragma once

#include "movement_cluster.h"
#include "movement_iterator.h"


class Parallel_movement: public Movement_cluster {
public:
    Parallel_movement(Body& body);
    bool make_step() override;
    // void add_movement(Movement_iterator* movement) override;
    // void add_movements(std::vector<Movement_iterator*> movements) override;
private:
    // std::vector<Movement_iterator*> movements;
    int current_step_index;
};
