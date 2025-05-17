#pragma once
#include "point.h"
#include "head.h"
#include "body_segment.h"


#define SCALE 0.2

#define HEAD_RADIUS 50 * SCALE
#define NECK_LENGTH 50 * SCALE
#define SPINE_LENGTH 300 * SCALE
#define FEMUR_LENGTH 250 * SCALE
#define TIBIA_LENGTH 250 * SCALE
#define FOOT_LENGTH 100 * SCALE
#define CLAVICLE_LENGTH 100 * SCALE
#define HUMERUS_LENGTH 150 * SCALE
#define RADIUS_LENGTH 150 * SCALE

#define BODY_HEIGHT TIBIA_LENGTH + FEMUR_LENGTH + SPINE_LENGTH

class Body_visitor;

// TODO: Do I want to make this a composite also?
class Body {
    public:
        Body();
        Body(float dx, float sy);

        Body_segment& get_l_femur();
        Body_segment& get_r_femur();
        Body_segment& get_l_tibia();
        Body_segment& get_r_tibia();
        Body_segment& get_spine();
        Body_segment& get_l_clavicle();
        Body_segment& get_r_clavicle();
        Body_segment& get_l_humerus();
        Body_segment& get_r_humerus();
        Body_segment& get_l_radius();
        Body_segment& get_r_radius();
        Body_segment& get_l_foot();
        Body_segment& get_r_foot();
        Body_segment& get_neck();
        Head& get_head();

        void accept(Body_visitor* visitor);

        void shift(float dx, float dy);

    private:
        Point axis;
        Point c4;
        Point t1;
        Point l_shoulder;
        Point r_shoulder;
        Point l_elbow;
        Point r_elbow;
        Point l_wrist;
        Point r_wrist;
        Point hip;
        Point l_knee;
        Point r_knee;
        Point l_ankle;
        Point r_ankle;

        Point l_foot_end;
        Point r_foot_end;

        Head head;
        Body_segment neck;
        Body_segment spine;
        Body_segment l_clavicle;
        Body_segment r_clavicle;
        Body_segment l_humerus;
        Body_segment r_humerus;
        Body_segment l_radius;
        Body_segment r_radius;
        Body_segment l_femur;
        Body_segment r_femur;
        Body_segment l_tibia;
        Body_segment r_tibia;
        Body_segment l_foot;
        Body_segment r_foot;
};