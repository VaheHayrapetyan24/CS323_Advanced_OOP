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

    l_thumb_end(dx, l_wrist.get_y() + THUMB_LENGTH),
    l_index_finger_end(dx, l_wrist.get_y() + INDEX_FINGER_LENGTH),
    l_middle_finger_end(dx, l_wrist.get_y() + MIDDLE_FINGER_LENGTH),
    l_ring_finger_end(dx, l_wrist.get_y() + RING_FINGER_LENGTH),
    l_pinky_finger_end(dx, l_wrist.get_y() + PINKY_FINGER_LENGTH),

    r_thumb_end(dx, r_wrist.get_y() + THUMB_LENGTH),
    r_index_finger_end(dx,r_wrist.get_y() + INDEX_FINGER_LENGTH),
    r_middle_finger_end(dx,r_wrist.get_y() + MIDDLE_FINGER_LENGTH),
    r_ring_finger_end(dx,r_wrist.get_y() + RING_FINGER_LENGTH),
    r_pinky_finger_end(dx,r_wrist.get_y() + PINKY_FINGER_LENGTH),

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
    r_femur(hip, r_knee),

    l_thumb(l_wrist, l_thumb_end),
    l_index_finger(l_wrist, l_index_finger_end),
    l_middle_finger(l_wrist, l_middle_finger_end),
    l_ring_finger(l_wrist, l_ring_finger_end),
    l_pinky_finger(l_wrist, l_pinky_finger_end),

    r_thumb(r_wrist, r_thumb_end),
    r_index_finger(r_wrist, r_index_finger_end),
    r_middle_finger(r_wrist, r_middle_finger_end),
    r_ring_finger(r_wrist, r_ring_finger_end),
    r_pinky_finger(r_wrist, r_pinky_finger_end)
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

    l_radius.add_subpart(&l_thumb);
    l_radius.add_subpart(&l_index_finger);
    l_radius.add_subpart(&l_middle_finger);
    l_radius.add_subpart(&l_ring_finger);
    l_radius.add_subpart(&l_pinky_finger);

    r_radius.add_subpart(&r_thumb);
    r_radius.add_subpart(&r_index_finger);
    r_radius.add_subpart(&r_middle_finger);
    r_radius.add_subpart(&r_ring_finger);
    r_radius.add_subpart(&r_pinky_finger);

    r_clavicle.rotate(-M_PI_2);
    l_clavicle.rotate(M_PI_2);

    r_foot.rotate(M_PI_2);
    l_foot.rotate(M_PI_2);

    r_humerus.rotate(-M_PI_2);
    l_humerus.rotate(M_PI_2);

    l_thumb.rotate(M_PI_4);
    l_middle_finger.rotate(- M_PI / 12);
    l_ring_finger.rotate(- M_PI / 6);
    l_pinky_finger.rotate(- 3 * M_PI / 12);

    r_thumb.rotate(- M_PI_4);
    r_middle_finger.rotate(M_PI / 12);
    r_ring_finger.rotate(M_PI / 6);
    r_pinky_finger.rotate(3 * M_PI / 12);
}

void Body::accept(Body_visitor* visitor) {
    visitor->visit(this);
}

void Body::shift(float dx, float dy) {
    l_femur.shift(dx, dy, false);
    r_femur.shift(dx, dy, false);
    spine.shift(dx, dy);
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