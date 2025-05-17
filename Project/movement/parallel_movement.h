#pragma once

#include "movement.h"
#include "movement_cluster.h"
#include "parallel_movement_iterator.h"


class Parallel_movement: public Movement_cluster {
public:
    std::unique_ptr<Movement_iterator> initiate() override;
};
