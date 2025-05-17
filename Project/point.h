#pragma once
#include <cmath>

class Point
{
public:
Point();
Point(Point&);
Point(float new_x, float new_y);

	float get_x();
	float get_y();
	int int_x();
	int int_y();

	float dist(Point& that);
	// float dist(const Point& that);

	float dir(Point& that);

	void shift(float dx, float dy);
	void rotate_around(float x, float y, float phi);

private:
	float x, y;
};

