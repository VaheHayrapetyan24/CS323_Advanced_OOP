#include "animate.h"
#include "body.h"
#include "movement/basic_movement.h"
#include "movement/sequential_movement.h"
#include "movement/parallel_movement.h"

std::unique_ptr<Parallel_movement> Animate::_step_forward = nullptr;

Parallel_movement& Animate::step_forward(Body& body) {
    if (!_step_forward) {
        printf("in the if \n");

        auto a = std::make_unique<Basic_movement>(
            body, -M_PI / 8, 300,
            [](Body& body, float target) { body.get_l_femur().rotate(target); },
            [](Body& body) { return body.get_l_femur().slope(); }
        );


        // Dynamically allocate Basic_movement objects
        auto a = std::make_unique<Basic_movement>(
            body, -M_PI / 8, 300,
            [](Body& body, float target) { body.get_l_femur().rotate(target); },
            [](Body& body) { return body.get_l_femur().slope(); }
        );

        auto b = std::make_unique<Basic_movement>(
            body, -3 * M_PI / 8, 250,
            [](Body& body, float target) { body.get_l_tibia().rotate(target); }
        );

        // Create the Parallel_movement object
        _step_forward = std::make_unique<Parallel_movement>(body);

        // Transfer ownership of the movements to _step_forward
        _step_forward->add_movement(a.release());
        _step_forward->add_movement(b.release());
    }

    printf("returning forward\n");
    return *_step_forward;
}
