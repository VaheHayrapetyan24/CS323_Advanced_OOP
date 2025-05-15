#pragma once

#include "movement_cluster.h"
#include "movement_iterator.h"


class Parallel_movement: public Movement_cluster {
public:
    Parallel_movement(Body& body);
    bool make_step() override;
private:
    int current_step_index;
};
