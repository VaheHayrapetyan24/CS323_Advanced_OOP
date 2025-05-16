// #include <cmath>
// #include <iostream>

// double calculate_rotation_angle(double x1, double y1, double x2, double y2, double px, double py) {
//     double dx = x2 - x1;
//     double dy = y2 - y1;
//     double px_rel = px - x1;
//     double py_rel = py - y1;

//     double numerator = px_rel * dy - py_rel * dx;
//     double denominator = px_rel * dx + py_rel * dy;

//     return atan2(numerator, denominator);
// }

// int main() {
//     double x1 = 0, y1 = 0; // Start of the line
//     double x2 = 1, y2 = 0; // End of the line
//     double px = 1, py = 3; // Point

//     double angle = calculate_rotation_angle(x1, y1, x2, y2, px, py);
//     std::cout << "Rotation angle (radians): " << angle << std::endl;
//     std::cout << "Rotation angle (degrees): " << angle * 180 / M_PI << std::endl;

//     return 0;
// }