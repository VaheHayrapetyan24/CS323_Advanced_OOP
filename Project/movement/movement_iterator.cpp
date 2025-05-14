#include "movement_iterator.h"
#include <iostream>
#include <cmath> // For M_PI

// MovementIterator::MovementIterator(Body& body, int steps): body(body), steps(steps), completed_steps(0) {
//     std::cout << "Initializing MovementIterator with completed_steps = 0" << std::endl;

//     femur_angle = 0;
//     tibia_angle = -M_PI / 2;

//     std::cout << "Femur slope before rotation: " << body.get_l_femur().get_line().slope() << std::endl;
//     std::cout << "Tibia slope before rotation: " << body.get_l_tibia().get_line().slope() << std::endl;

    
// }

//     // Perform a single step
// bool MovementIterator::make_step() {
//     // std::cout << "Completed steps: " << completed_steps << std::endl;
//     if (completed_steps >= steps) {
//         return false;
//     }


//     // std::cout << "Rotating femur, current: x " << body.get_l_femur().get_line().get_end().get_x() << std::endl;

//     float d_femur = (femur_angle - body.get_l_femur().get_line().slope()) / (steps - completed_steps);


//     // std::cout << "Rotating femur by " << fabs(d_femur) << " " << (fabs(d_femur) < 1e-6) << std::endl;

//     // // if (fabs(d_femur) > 1e-6) {
//         body.get_l_femur().rotate(d_femur);
//     // }

//     float d_tibia = (tibia_angle - body.get_l_tibia().get_line().slope()) / (steps - completed_steps);

    
//     // // if (fabs(d_tibia) > 1e-6) {
//         body.get_l_tibia().rotate(d_tibia);
//     // }

//     // std::cout << "Femur slope after rotation: " << body.get_l_femur().get_line().slope() << " length " << body.get_l_femur().get_line().length() << std::endl;
//     // std::cout << "Tibia slope after rotation: " << body.get_l_tibia().get_line().slope() << " length " << body.get_l_tibia().get_line().length() << std::endl;
//     completed_steps++;


//     return true;
// }

Movement_iterator::Movement_iterator(Body& body): body(body) {}