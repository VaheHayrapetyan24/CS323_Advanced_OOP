#pragma once

#include "body.h"
#include "body_segment.h"
#include "movement/basic_movement.h"
#include "movement/sequential_movement.h"
#include "movement/movement_iterator.h"
#include "movement/parallel_movement.h"


class Animate {
public:
    Animate(Body& body);
    std::unique_ptr<Movement_iterator> step_forward_iterator();
    std::unique_ptr<Movement_iterator> stand_upright_iterator();
private:
    Sequential_movement* make_forward_movement(
        Body_segment* femurs[2],
        Body_segment* tibias[2], 
        Body_segment* feet[2],
        Body_segment* radii[2],
        Body_segment* humeri[2]
    );
    Sequential_movement* make_stand_upright_movement();
    Sequential_movement* l_step_forward;
    Sequential_movement* r_step_forward;

    Sequential_movement* stand_upright;
    Body& body;
};
