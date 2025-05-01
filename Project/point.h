#pragma once
#include <cmath>;

class Point
{
public:
Point();
Point(Point&);
Point(double new_x, double new_y);

	double get_x();
	double get_y();
	int int_x();
	int int_y();

	double dist(Point& that);
	double dir(Point& that);

	void shift(double dx, double dy);

private:
	double x, y;
};

