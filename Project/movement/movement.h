#pragma once

#include "../body.h"
#include "movement_iterator.h"


class Movement {
public:
    Movement(Body& body);
    virtual Movement_iterator initiate() = 0;
protected:
    Body& body;
};