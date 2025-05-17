#include "point.h"
#include "line.h"
#include <iostream>

Line::Line(Point& p1, Point& p2): start{p1}, end{p2}, original_length{length()} {}

Point& Line::get_start() {
    return start;
}


Point& Line::get_end() {
    return end;
}

float Line::slope() {
    return start.dir(end);
}

float Line::length() {
    // return original_length;
    return start.dist(end);
}

void Line::shift(float dx, float dy) {
    start.shift(dx, dy);
    end.shift(dx, dy);
}

void Line::rotate(float da) {
    
    float ang = slope() + da, len = original_length;
    end.shift(
        start.get_x() + len * cos(ang) - end.get_x(), 
        start.get_y() + len * sin(ang) - end.get_y());
}



void Line::rotate_around(float x, float y, float phi) {
    printf("rotate_around %f, %f, %f\n", x, y, phi);
    printf("Start Point: (%f, %f), End Point: (%f, %f)\n", 
           start.get_x(), start.get_y(), end.get_x(), end.get_y());
    start.rotate_around(x, y, phi);
    end.rotate_around(x, y, phi);

    printf("After Rotation - Start Point: (%f, %f), End Point: (%f, %f)\n", 
           start.get_x(), start.get_y(), end.get_x(), end.get_y());

    float distance = sqrt((start.get_x() - end.get_x()) * (start.get_x() - end.get_x()) + (start.get_y() - end.get_y()) * (start.get_y() - end.get_y()));

    if (fabs(fabs(original_length / distance) - 1) > 1e-2) {
        printf("correcting\n");
        float x_diff = (end.get_x() - start.get_x()) * (original_length / distance);
        float y_diff = (end.get_y() - start.get_y()) * (original_length / distance);
        printf("Original length: %f, Current distance: %f\n", original_length, distance);
        printf("x_diff: %f, y_diff: %f\n", x_diff, y_diff);

        end.shift(start.get_x() + x_diff - end.get_x(), start.get_y() + y_diff - end.get_y());        
    }
}