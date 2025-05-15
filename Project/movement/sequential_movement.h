#pragma once

#include "movement_cluster.h"
#include "movement_iterator.h"


class Sequential_movement: public Movement_cluster {
public:
    Sequential_movement(Body& body);
    bool make_step() override;
private:
    int current_movement_index;
};
