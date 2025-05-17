#pragma once

#include "movement_cluster.h"
#include "movement_iterator.h"
#include "sequential_movement_iterator.h"


class Sequential_movement: public Movement_cluster {
public:
    std::unique_ptr<Movement_iterator> initiate() override;
};
