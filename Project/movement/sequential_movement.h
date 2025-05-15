#pragma once

#include "movement_cluster.h"
#include "movement_iterator.h"
#include "sequential_movement_iterator.h"


class Sequential_movement: public Movement_cluster {
public:
    Sequential_movement(Body& body);
    Movement_iterator initiate() override;
    // bool make_step() override;
// private:
//     int current_movement_index;
};
