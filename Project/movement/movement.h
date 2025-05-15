#pragma once

#include "movement_iterator.h"
#include "../body.h"

#include <memory>

class Movement {
public:
    Movement(Body& body);
    virtual std::unique_ptr<Movement_iterator> initiate() = 0;
protected:
    Body& body;
};