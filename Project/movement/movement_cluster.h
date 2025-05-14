#pragma once

#include "movement_iterator.h"

class Movement_cluster: public Movement_iterator {
public:
    Movement_cluster(Body& body);
    virtual void add_movement(Movement_iterator* movement);
    virtual void add_movements(std::vector<Movement_iterator*> movements);
protected:
    std::vector<Movement_iterator*> movements;
};