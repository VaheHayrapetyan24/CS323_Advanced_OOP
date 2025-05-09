#include "body.h"
#include "line.h"


Body::Body(): 
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
}