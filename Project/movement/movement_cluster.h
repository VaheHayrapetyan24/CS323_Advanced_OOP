#pragma once

// #include "movement_iterator.h"
#include "movement.h"

class Movement_cluster: public Movement {
public:
    Movement_cluster(Body& body);
    virtual void add_movement(Movement* movement);
    virtual void add_movements(std::vector<Movement*> movements);
protected:
    std::vector<Movement*> movements;
};