#pragma once

#include "movement.h"

class Movement_cluster: public Movement {
public:
    ~Movement_cluster();
    virtual void add_movement(Movement* movement);
    virtual void add_movements(std::vector<Movement*> movements);
protected:
    std::vector<Movement*> movements;
};