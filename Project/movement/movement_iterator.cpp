#include "movement_iterator.h"
#include <iostream>

Movement_iterator::Movement_iterator(Body& body): body(body) {}

bool Movement_iterator::make_step() {
    return false;
}