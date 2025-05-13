#pragma once
#include "point.h"
#include "head.h"
#include "body_segment.h"

class Body_visitor;

// TODO: Do I want to make this a composite also?
class Body {
    public:
        Body();
        Body(float dx, float sy);
        // void set_axis(const Point& axis);
        // void set_c4(const Point& c4);
        // void set_t1(const Point& t1);
        // void set_l_shoulder(const Point& l_shoulder);
        // void set_r_shoulder(const Point& r_shoulder);
        // void set_l_elbow(const Point& l_elbow);
        // void set_r_elbow(const Point& r_elbow);
        // void set_l_wrist(const Point& l_wrist);
        // void set_r_wrist(const Point& r_wrist);
        // void set_hip(const Point& hip);
        // void set_l_knee(const Point& l_knee);
        // void set_r_knee(const Point& r_knee);
        // void set_l_ankle(const Point& l_ankle);
        // void set_r_ankle(const Point& r_ankle);

        Body_segment& get_l_femur();
        Body_segment& get_r_femur();
        Body_segment& get_l_tibia();
        Body_segment& get_spine();

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

        // Line l_clavicle_line;
        // Line neck_line;
        // Line r_clavicle_line;
        // Line l_humerus_line;
        // Line r_humerus_line;
        // Line l_radius_line;
        // Line r_radius_line;
        // Line spine_line;
        // Line l_femur_line;
        // Line r_femur_line;
        // Line l_tibia_line;
        // Line r_tibia_line;    
        // Line l_foot_line;
        // Line r_foot_line;

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