#pragma once

#include "movement_iterator.h"
#include "../body.h"

#include <memory>

class Movement {
public:
    virtual std::unique_ptr<Movement_iterator> initiate() = 0;
};