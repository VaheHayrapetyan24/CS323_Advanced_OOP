#pragma once

#include "movement_iterator.h"
#include "movement.h"

class Sequential_movement;

class Sequential_movement_iterator: public Movement_iterator {
friend class Sequential_movement;
public:
    bool make_step() override;
private:
    Sequential_movement_iterator(Body& body, std::vector<Movement*> &movements);
    std::vector<Movement_iterator> movements;
    int current_movement_index;
};