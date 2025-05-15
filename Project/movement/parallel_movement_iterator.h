#pragma once

#include "movement_iterator.h"
#include "movement.h"

class Parallel_movement;

class Parallel_movement_iterator: public Movement_iterator {
friend class Parallel_movement;
public:
    bool make_step() override;
private:
    Parallel_movement_iterator(Body& body, std::vector<Movement*> &movements);
    std::vector<Movement_iterator> movements;
};