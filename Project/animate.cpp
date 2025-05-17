#include "animate.h"
#include "body.h"
#include "movement/basic_movement.h"
#include "movement/sequential_movement.h"
#include "movement/parallel_movement.h"

#define SPEED 1


// float calculate_rotation_angle(float x1, float y1, float x2, float y2, float px, float py) {
//     float dx = x2 - x1;
//     float dy = y2 - y1;
//     float px_rel = px - x1;
//     float py_rel = py - y1;

//     float numerator = px_rel * dy - py_rel * dx;
//     float denominator = px_rel * dx + py_rel * dy;

//     return atan2(numerator, denominator);
// }

Animate::Animate(Body& body) : body(body) {
    // Use unique_ptr for femurs, tibias, and feet arrays
    auto femurs = std::make_unique<Body_segment*[]>(2);
    auto tibias = std::make_unique<Body_segment*[]>(2);
    auto feet = std::make_unique<Body_segment*[]>(2);

    femurs[0] = &body.get_l_femur();
    femurs[1] = &body.get_r_femur();
    tibias[0] = &body.get_l_tibia();
    tibias[1] = &body.get_r_tibia();
    feet[0] = &body.get_l_foot();
    feet[1] = &body.get_r_foot();

    l_step_forward = make_forward_movement(femurs.get(), tibias.get(), feet.get());

    femurs[0] = &body.get_r_femur();
    femurs[1] = &body.get_l_femur();
    tibias[0] = &body.get_r_tibia();
    tibias[1] = &body.get_l_tibia();
    feet[0] = &body.get_r_foot();
    feet[1] = &body.get_l_foot();

    r_step_forward = make_forward_movement(femurs.get(), tibias.get(), feet.get());

    stand_upright = make_stand_upright_movement();
}

std::unique_ptr<Movement_iterator> Animate::step_forward_iterator() {
    if (body.get_l_foot().get_line().get_end().get_x() > body.get_r_foot().get_line().get_end().get_x()) {
        return r_step_forward->initiate();
    }

    return l_step_forward->initiate();
}

std::unique_ptr<Movement_iterator> Animate::stand_upright_iterator() {
    return stand_upright->initiate();
}

Sequential_movement* Animate::make_forward_movement(Body_segment* femurs[2], Body_segment* tibias[2], Body_segment* feet[2]) {
    Body_segment* b_femur = femurs[0];
    Body_segment* f_femur = femurs[1];
    Body_segment* b_tibia = tibias[0];
    Body_segment* f_tibia = tibias[1];
    Body_segment* b_foot = feet[0];
    Body_segment* f_foot = feet[1];
    
    auto b_leg_up = std::make_unique<Parallel_movement>(body);

    auto b_femur_up = std::make_unique<Basic_movement>(
        body, - M_PI / 4, 400 * SPEED,
        [b_femur](Body& body, float target) { b_femur->rotate(target); },
        [b_femur](Body& body) { return b_femur->slope(); }
    );
    auto b_tibia_up = std::make_unique<Basic_movement>(
        body, -3 * M_PI / 4, 350 * SPEED,
        [b_tibia](Body& body, float target) { b_tibia->rotate(target); },
        [b_tibia](Body& body) { return b_tibia->slope(); }
    );

    // TODO: doesn't this just defeat the whole purpose of unique pointer?
    // f_leg_up->add_movement(b_foot_fix.release());
    b_leg_up->add_movement(b_femur_up.release());
    b_leg_up->add_movement(b_tibia_up.release());

    auto f_leg_straighten = std::make_unique<Parallel_movement>(body);
    f_leg_straighten->add_movement(std::make_unique<Basic_movement>(
        body, -3 * M_PI / 8, 100 * SPEED,
        [f_femur](Body& body, float target) { f_femur->rotate(target); },
        [f_femur](Body& body) { return f_femur->slope(); }
    ).release());
    f_leg_straighten->add_movement(std::make_unique<Basic_movement>(
        body, - 3 * M_PI / 8, 100 * SPEED,
        [f_tibia](Body& body, float target) { f_tibia->rotate(target); },
        [f_tibia](Body& body) { return f_tibia->slope(); }
    ).release());
    f_leg_straighten->add_movement(std::make_unique<Basic_movement>(
        body, M_PI / 8, 100 * SPEED,
        [f_foot](Body& body, float target) { f_foot->rotate(target); },
        [f_foot](Body& body) { return f_foot->slope(); }
    ).release());



    auto f_go_back_b_up = std::make_unique<Parallel_movement>(body);
    f_go_back_b_up->add_movement(b_leg_up.release());
    f_go_back_b_up->add_movement(std::make_unique<Basic_movement>(
        body, - 9 * M_PI / 16, 400 * SPEED,
        [f_femur, f_foot](Body& body, float target) { 
            float orig_x = f_foot->get_line().get_start().get_x();
            f_femur->rotate(target);
            float new_x = f_foot->get_line().get_start().get_x();
            body.shift(orig_x - new_x, 0);
        },
        [f_femur](Body& body) { return f_femur->slope(); }
    ).release());


    auto b_straighen = std::make_unique<Parallel_movement>(body);
    b_straighen->add_movement(std::make_unique<Basic_movement>(
        body, -3 * M_PI / 8, 200 * SPEED,
        [b_femur](Body& body, float target) { b_femur->rotate(target); },
        [b_femur](Body& body) { return b_femur->slope(); }
    ).release());
    b_straighen->add_movement(std::make_unique<Basic_movement>(
        body, - 3 * M_PI / 8, 200 * SPEED,
        [b_tibia](Body& body, float target) { b_tibia->rotate(target); },
        [b_tibia](Body& body) { return b_tibia->slope(); }
    ).release());
    b_straighen->add_movement(std::make_unique<Basic_movement>(
        body, M_PI / 8, 100 * SPEED,
        [b_foot](Body& body, float target) { b_foot->rotate(target); },
        [b_foot](Body& body) { return b_foot->slope(); }
    ).release());


    auto b_straigten_f_tibia_rotate = std::make_unique<Parallel_movement>(body);
    b_straigten_f_tibia_rotate->add_movement(b_straighen.release());
    b_straigten_f_tibia_rotate->add_movement(std::make_unique<Basic_movement>(
        body, - 11 * M_PI / 16, 200 * SPEED,
        [f_tibia, f_foot](Body& body, float target) { 
            float orig_x = f_foot->get_line().get_end().get_x();
            f_tibia->rotate(target);
            float new_x = f_foot->get_line().get_end().get_x();
            body.shift(orig_x - new_x, 0);
        },
        [f_tibia](Body& body) { return f_tibia->slope(); }
    ).release());

    auto legs_prepare = std::make_unique<Sequential_movement>(body);
    legs_prepare->add_movement(f_leg_straighten.release());
    legs_prepare->add_movement(f_go_back_b_up.release());
    legs_prepare->add_movement(b_straigten_f_tibia_rotate.release());
    

    std::unique_ptr<Sequential_movement> movement = std::make_unique<Sequential_movement>(body);
    movement->add_movement(legs_prepare.release());

    return movement.release();
}

Sequential_movement* Animate::make_stand_upright_movement() {
    auto l_leg_straighten = std::make_unique<Parallel_movement>(body);
    l_leg_straighten->add_movement(std::make_unique<Basic_movement>(
        body, - M_PI_2, 100 * SPEED,
        [](Body& body, float target) { body.get_l_femur().rotate(target); },
        [](Body& body) { return body.get_l_femur().slope(); }
    ).release());
    l_leg_straighten->add_movement(std::make_unique<Basic_movement>(
        body, - M_PI_2, 100 * SPEED,
        [](Body& body, float target) { body.get_l_tibia().rotate(target); },
        [](Body& body) { return body.get_l_tibia().slope(); }
    ).release());
    l_leg_straighten->add_movement(std::make_unique<Basic_movement>(
        body, 0, 100 * SPEED,
        [](Body& body, float target) { body.get_l_foot().rotate(target); },
        [](Body& body) { return body.get_l_foot().slope(); }
    ).release());

    auto r_leg_straighten = std::make_unique<Parallel_movement>(body);
    r_leg_straighten->add_movement(std::make_unique<Basic_movement>(
        body, - M_PI_2, 100 * SPEED,
        [](Body& body, float target) { body.get_r_femur().rotate(target); },
        [](Body& body) { return body.get_r_femur().slope(); }
    ).release());
    r_leg_straighten->add_movement(std::make_unique<Basic_movement>(
        body, - M_PI_2, 100 * SPEED,
        [](Body& body, float target) { body.get_r_tibia().rotate(target); },
        [](Body& body) { return body.get_r_tibia().slope(); }
    ).release());
    r_leg_straighten->add_movement(std::make_unique<Basic_movement>(
        body, 0, 100 * SPEED,
        [](Body& body, float target) { body.get_r_foot().rotate(target); },
        [](Body& body) { return body.get_r_foot().slope(); }
    ).release());


    std::unique_ptr<Sequential_movement> movement = std::make_unique<Sequential_movement>(body);
    movement->add_movement(l_leg_straighten.release());
    movement->add_movement(r_leg_straighten.release());


    return movement.release();
}