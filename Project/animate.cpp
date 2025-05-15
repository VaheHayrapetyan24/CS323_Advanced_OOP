#include "animate.h"
#include "body.h"
#include "movement/basic_movement.h"
#include "movement/sequential_movement.h"
#include "movement/parallel_movement.h"

#define SPEED 10

std::unique_ptr<Sequential_movement> Animate::_step_forward = nullptr;

Sequential_movement& Animate::step_forward(Body& body) {
    if (!_step_forward) {
        printf("in the if \n");

        auto l_leg_up = std::make_unique<Parallel_movement>(body);

        auto b_foot_fix = std::make_unique<Basic_movement>(
            body, 0, 1,
            [](Body& body, float target) { body.get_l_foot().rotate(target); },
            [](Body& body) { return body.get_l_foot().slope(); }
        );
        auto l_femur_up = std::make_unique<Basic_movement>(
            body, - M_PI / 4, 400 * SPEED,
            [](Body& body, float target) { body.get_l_femur().rotate(target); },
            [](Body& body) { return body.get_l_femur().slope(); }
        );
        auto l_tibia_up = std::make_unique<Basic_movement>(
            body, -3 * M_PI / 4, 350 * SPEED,
            [](Body& body, float target) { body.get_l_tibia().rotate(target); },
            [](Body& body) { return body.get_l_tibia().slope(); }
        );

        // TODO: doesn't this just defeat the whole purpose of unique pointer?
        l_leg_up->add_movement(b_foot_fix.release());
        l_leg_up->add_movement(l_femur_up.release());
        l_leg_up->add_movement(l_tibia_up.release());

        auto r_leg_straighten = std::make_unique<Parallel_movement>(body);
        r_leg_straighten->add_movement(std::make_unique<Basic_movement>(
            body, -3 * M_PI / 8, 100 * SPEED,
            [](Body& body, float target) { body.get_r_femur().rotate(target); },
            [](Body& body) { return body.get_r_femur().slope(); }
        ).release());
        r_leg_straighten->add_movement(std::make_unique<Basic_movement>(
            body, - 3 * M_PI / 8, 100 * SPEED,
            [](Body& body, float target) { body.get_r_tibia().rotate(target); },
            [](Body& body) { return body.get_r_tibia().slope(); }
        ).release());
        r_leg_straighten->add_movement(std::make_unique<Basic_movement>(
            body, M_PI / 8, 100 * SPEED,
            [](Body& body, float target) { body.get_r_foot().rotate(target); },
            [](Body& body) { return body.get_r_foot().slope(); }
        ).release());



        auto r_go_back_l_up = std::make_unique<Parallel_movement>(body);
        r_go_back_l_up->add_movement(l_leg_up.release());
        r_go_back_l_up->add_movement(std::make_unique<Basic_movement>(
            body, - 9 * M_PI / 16, 400 * SPEED,
            [](Body& body, float target) { body.get_r_femur().rotate(target); },
            [](Body& body) { return body.get_r_femur().slope(); }
        ).release());


        auto l_straighen = std::make_unique<Parallel_movement>(body);
        l_straighen->add_movement(std::make_unique<Basic_movement>(
            body, -3 * M_PI / 8, 200 * SPEED,
            [](Body& body, float target) { body.get_l_femur().rotate(target); },
            [](Body& body) { return body.get_l_femur().slope(); }
        ).release());
        l_straighen->add_movement(std::make_unique<Basic_movement>(
            body, - 3 * M_PI / 8, 200 * SPEED,
            [](Body& body, float target) { body.get_l_tibia().rotate(target); },
            [](Body& body) { return body.get_l_tibia().slope(); }
        ).release());
        l_straighen->add_movement(std::make_unique<Basic_movement>(
            body, M_PI / 8, 100 * SPEED,
            [](Body& body, float target) { body.get_l_foot().rotate(target); },
            [](Body& body) { return body.get_l_foot().slope(); }
        ).release());


        auto l_straigten_r_tibia_rotate = std::make_unique<Parallel_movement>(body);
        l_straigten_r_tibia_rotate->add_movement(l_straighen.release());
        l_straigten_r_tibia_rotate->add_movement(std::make_unique<Basic_movement>(
            body, - 11 * M_PI / 16, 200 * SPEED,
            [](Body& body, float target) { body.get_r_tibia().rotate(target); },
            [](Body& body) { return body.get_r_tibia().slope(); }
        ).release());

        auto legs_prepare = std::make_unique<Sequential_movement>(body);
        legs_prepare->add_movement(r_leg_straighten.release());
        legs_prepare->add_movement(r_go_back_l_up.release());
        legs_prepare->add_movement(l_straigten_r_tibia_rotate.release());



        
        // second_phase->add_movement(std::make_unique<Basic_movement>(
        //     body, - M_PI / 8, 500 * SPEED,
        //     [](Body& body, float target) { body.get_l_femur().rotate(target); },
        //     [](Body& body) { return body.get_l_femur().slope(); }
        // ).release());
        



        

        _step_forward = std::make_unique<Sequential_movement>(body);
        _step_forward->add_movement(legs_prepare.release());
        // _step_forward->add_movement(second_phase.release());
    }

    printf("returning forward\n");
    return *_step_forward;
}
