#pragma once
#include "point.h"
#include "head.h"
#include "body_segment.h"


#define SCALE 1 / 4

#define HEAD_RADIUS 50 * SCALE
#define NECK_LENGTH 50 * SCALE
#define SPINE_LENGTH 300 * SCALE
#define FEMUR_LENGTH 250 * SCALE
#define TIBIA_LENGTH 250 * SCALE
#define FOOT_LENGTH 100 * SCALE
#define CLAVICLE_LENGTH 50 * SCALE
#define HUMERUS_LENGTH 150 * SCALE
#define RADIUS_LENGTH 150 * SCALE

#define THUMB_LENGTH 50 * SCALE
#define INDEX_FINGER_LENGTH 70 * SCALE
#define MIDDLE_FINGER_LENGTH 80 * SCALE
#define RING_FINGER_LENGTH 70 * SCALE
#define PINKY_FINGER_LENGTH 60 * SCALE

#define BODY_HEIGHT TIBIA_LENGTH + FEMUR_LENGTH + SPINE_LENGTH

class Body_visitor;

// TODO: Do I want to make this a composite also?
class Body {
    public:
        Body();
        Body(float dx, float sy);

        Head& get_head();
        
        Body_segment& get_neck();
        Body_segment& get_spine();

        Body_segment& get_l_clavicle();
        Body_segment& get_r_clavicle();
        Body_segment& get_l_humerus();
        Body_segment& get_r_humerus();
        Body_segment& get_l_radius();
        Body_segment& get_r_radius();
        
        Body_segment& get_l_thumb();
        Body_segment& get_l_index_finger();
        Body_segment& get_l_middle_finger();
        Body_segment& get_l_ring_finger();
        Body_segment& get_l_pinky_finger();
        Body_segment& get_r_thumb();
        Body_segment& get_r_index_finger();
        Body_segment& get_r_middle_finger();
        Body_segment& get_r_ring_finger();
        Body_segment& get_r_pinky_finger();

        Body_segment& get_l_femur();
        Body_segment& get_r_femur();
        Body_segment& get_l_tibia();
        Body_segment& get_r_tibia();
        Body_segment& get_l_foot();
        Body_segment& get_r_foot();

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

        Point l_thumb_end;
        Point l_index_finger_end;
        Point l_middle_finger_end;
        Point l_ring_finger_end;
        Point l_pinky_finger_end;

        Point r_thumb_end;
        Point r_index_finger_end;
        Point r_middle_finger_end;
        Point r_ring_finger_end;
        Point r_pinky_finger_end;

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

        Body_segment l_thumb;
        Body_segment l_index_finger;
        Body_segment l_middle_finger;
        Body_segment l_ring_finger;
        Body_segment l_pinky_finger;

        Body_segment r_thumb;
        Body_segment r_index_finger;
        Body_segment r_middle_finger;
        Body_segment r_ring_finger;
        Body_segment r_pinky_finger;
};