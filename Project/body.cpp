#include "body.h"
#include "line.h"
#include "body_visitor.h"

Body::Body(): Body(0, 0){}

Body::Body(float dx, float sy):
    l_foot_end(dx - 150, sy),
    r_foot_end(dx + 150, sy),

    l_ankle(dx - 50, sy),
    r_ankle(dx + 50, sy),

    l_knee(dx - 50, sy + 250),
    r_knee(dx + 50, sy + 250),

    hip(dx, sy + (250 + 245)),
    t1(dx, sy + (250 + 245 + 300)),
    c4(dx, sy + (250 + 245 + 300 + 70)),
    axis(dx, sy + (250 + 245 + 300 + 50 + 80)),

    l_shoulder(dx - 100, sy + (250 + 245 + 300)),
    r_shoulder(dx + 100, sy + (250 + 245 + 300)),

    l_elbow(dx - 150, sy + (250 + 245 + 150)),
    r_elbow(dx + 150, sy + (250 + 245 + 150)),

    l_wrist(dx - 100, sy + (250 + 245)),
    r_wrist(dx + 100, sy + (250 + 245)),

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
    r_femur(hip, r_knee) {
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
}

void Body::accept(Body_visitor* visitor) {
    visitor->visit(this);
}

void Body::shift(float dx, float dy) {
    l_femur.shift(dx, dy);
    r_femur.shift(dx, dy);
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