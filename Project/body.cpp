#include "body.h"
#include "line.h"
#include "body_visitor.h"

Body::Body(): Body(0, 0){}

Body::Body(float dx, float sy):
    l_foot_end(dx, sy - FOOT_LENGTH),
    r_foot_end(dx, sy - FOOT_LENGTH),

    l_ankle(dx, sy),
    r_ankle(dx, sy),

    l_knee(dx, sy + TIBIA_LENGTH),
    r_knee(dx, sy + TIBIA_LENGTH),

    hip(dx, sy + TIBIA_LENGTH + FEMUR_LENGTH),
    t1(dx, sy + TIBIA_LENGTH + FEMUR_LENGTH + SPINE_LENGTH),
    c4(dx, sy + TIBIA_LENGTH + FEMUR_LENGTH + SPINE_LENGTH + NECK_LENGTH),
    axis(dx, sy + TIBIA_LENGTH + FEMUR_LENGTH + SPINE_LENGTH + NECK_LENGTH + HEAD_RADIUS),

    l_shoulder(dx, sy + TIBIA_LENGTH + FEMUR_LENGTH + SPINE_LENGTH + CLAVICLE_LENGTH),
    r_shoulder(dx, sy + TIBIA_LENGTH + FEMUR_LENGTH + SPINE_LENGTH + CLAVICLE_LENGTH),

    l_elbow(dx, sy + TIBIA_LENGTH + FEMUR_LENGTH + SPINE_LENGTH + CLAVICLE_LENGTH + HUMERUS_LENGTH),
    r_elbow(dx, sy + TIBIA_LENGTH + FEMUR_LENGTH + SPINE_LENGTH + CLAVICLE_LENGTH + HUMERUS_LENGTH),

    l_wrist(dx, sy + TIBIA_LENGTH + FEMUR_LENGTH + SPINE_LENGTH + CLAVICLE_LENGTH + HUMERUS_LENGTH + RADIUS_LENGTH),
    r_wrist(dx, sy + TIBIA_LENGTH + FEMUR_LENGTH + SPINE_LENGTH + CLAVICLE_LENGTH + HUMERUS_LENGTH + RADIUS_LENGTH),

    head(c4, axis),
    neck(t1, c4),
    l_radius(l_elbow, l_wrist),
    l_humerus(l_shoulder, l_elbow),
    l_clavicle(t1, l_shoulder),
    r_radius(r_elbow, r_wrist),
    r_humerus(r_shoulder, r_elbow),
    r_clavicle(t1, r_shoulder),

    spine(hip, t1),

    l_foot(l_ankle, l_foot_end),
    l_tibia(l_knee, l_ankle),   
    l_femur(hip, l_knee),

    r_foot(r_ankle, r_foot_end),
    r_tibia(r_knee, r_ankle),
    r_femur(hip, r_knee)
{   
    neck.add_subpart(&head);
    
    l_clavicle.add_subpart(&l_humerus);
    l_humerus.add_subpart(&l_radius);

    r_clavicle.add_subpart(&r_humerus);
    r_humerus.add_subpart(&r_radius);

    spine.add_subpart(&neck);
    spine.add_subpart(&l_clavicle);
    spine.add_subpart(&r_clavicle);

    l_femur.add_subpart(&l_tibia);
    l_tibia.add_subpart(&l_foot);

    r_femur.add_subpart(&r_tibia);
    r_tibia.add_subpart(&r_foot);

    r_clavicle.rotate(-M_PI_2);
    l_clavicle.rotate(M_PI_2);

    r_foot.rotate(M_PI_2);
    l_foot.rotate(M_PI_2);

    r_humerus.rotate(-M_PI_2);
    l_humerus.rotate(M_PI_2);
}

void Body::accept(Body_visitor* visitor) {
    visitor->visit(this);
}

// TODO: Fix shift like rotate
void Body::shift(float dx, float dy) {
    l_tibia.shift(dx, dy);
    r_tibia.shift(dx, dy);
    l_humerus.shift(dx, dy);
    r_humerus.shift(dx, dy);
    head.shift(dx, dy);
    t1.shift(dx, dy);
    hip.shift(dx, dy);
}

Body_segment& Body::get_l_femur() {
    return l_femur;
}
Body_segment& Body::get_r_femur() {
    return r_femur;
}
Body_segment& Body::get_spine() {
    return spine;
}

Body_segment& Body::get_l_tibia() {
    return l_tibia;
}

Body_segment& Body::get_r_tibia() {
    return r_tibia;
}
Body_segment& Body::get_l_foot() {
    return l_foot;
}

Body_segment& Body::get_r_foot() {
    return r_foot;
}

Body_segment& Body::get_l_clavicle() {
    return l_clavicle;
}

Body_segment& Body::get_r_clavicle() {
    return r_clavicle;
}

Body_segment& Body::get_l_humerus() {
    return l_humerus;
}

Body_segment& Body::get_r_humerus() {
    return r_humerus;
}

Body_segment& Body::get_l_radius() {
    return l_radius;
}

Body_segment& Body::get_r_radius() {
    return r_radius;
}

Body_segment& Body::get_neck() {
    return neck;
}

Head& Body::get_head() {
    return head;
}