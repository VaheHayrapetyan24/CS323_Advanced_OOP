#pragma once

#include <iostream>
#include <cmath> // For M_PI

#include "../body.h"

class Movement_iterator {
public:
    virtual bool make_step() = 0;
};