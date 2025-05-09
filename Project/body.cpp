#include "body.h"
#include "line.h"


Body::Body(): 
head(c4, axis),
l_clavicle_line(t1, l_shoulder),
neck_line(t1, c4),
r_clavicle_line(t1, r_shoulder),
l_humerus_line(l_shoulder, l_elbow),
r_humerus_line(r_shoulder, r_elbow),
l_radius_line(l_elbow, l_wrist),
r_radius_line(r_elbow, r_wrist),
spine_line(hip, t1),
l_femur_line(hip, l_knee),
r_femur_line(hip, r_knee),
l_tibia_line(l_knee, l_ankle),
r_tibia_line(r_knee, r_ankle),
l_foot_line(l_ankle, l_foot_end),
r_foot_line(r_ankle, r_foot_end),
neck(neck_line, new std::vector<Part*>{&head}),
l_radius(l_radius_line),
l_humerus(l_humerus_line, new std::vector<Part*>{&l_radius}),
l_clavicle(l_clavicle_line, new std::vector<Part*>{&l_humerus}),
r_radius(r_radius_line),
r_humerus(r_humerus_line, new std::vector<Part*>{&r_radius}),
r_clavicle(r_clavicle_line, new std::vector<Part*>{&r_humerus}),

spine(spine_line, new std::vector<Part*>{&neck, &l_clavicle, &r_clavicle}),

l_foot(l_foot_line),
l_tibia(l_tibia_line, new std::vector<Part*>{&l_foot}),
l_femur(l_femur_line, new std::vector<Part*>{&l_tibia}),

r_foot(r_foot_line),
r_tibia(r_tibia_line, new std::vector<Part*>{&r_foot}),
r_femur(r_femur_line, new std::vector<Part*>{&r_tibia})
{}