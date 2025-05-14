#pragma once

#include <iostream>
#include <cmath> // For M_PI

#include "../body.h"

class Movement_iterator {
public:
    Movement_iterator(Body& body);
    virtual bool make_step() = 0;
protected:
    Body& body;
};