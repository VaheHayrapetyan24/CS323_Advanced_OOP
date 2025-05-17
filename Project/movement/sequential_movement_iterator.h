#pragma once

#include "movement_iterator.h"
#include "movement.h"

class Sequential_movement;

class Sequential_movement_iterator: public Movement_iterator {
friend class Sequential_movement;
public:
    bool make_step() override;
    Sequential_movement_iterator(Body& body, std::vector<Movement*> &movements);
private:
    std::vector<std::unique_ptr<Movement_iterator>> movements;
    int current_movement_index;
};