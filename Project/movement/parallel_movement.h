#pragma once

#include "movement.h"
#include "movement_cluster.h"
#include "parallel_movement_iterator.h"


class Parallel_movement: public Movement_cluster {
public:
    Parallel_movement(Body& body);
    Movement_iterator initiate() override;
};
