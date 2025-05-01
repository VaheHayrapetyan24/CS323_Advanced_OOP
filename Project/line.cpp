#include "point.h"

class Line {
public:
    Line(Point& p1, Point& p2): start{p1}, end{p2} {}

    Point get_start() {
        return Point{start};
    }

    Point get_end() {
        return Point{end};
    }

    double slope() {
        return start.dir(end);
    }

    double length() {
        return start.dist(end);
    }

    void shift(double dx, double dy) {
        start.shift(dx, dy);
        end.shift(dx, dy);
    }

    void rotate(double da) {
        double ang = slope() + da, len = length();
        end.shift(
            start.get_x() + len * cos(ang) - end.get_x(), 
            start.get_y() + len * sin(ang) - end.get_y());
    }

private:
    // Line(Line& original): start{original.} {


    // }

    Point start, end;


};