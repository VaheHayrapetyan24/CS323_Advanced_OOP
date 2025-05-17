#include "point.h"
#include <iostream>

Point::Point(float new_x, float new_y) : x(new_x), y(new_y)
{

}


Point::Point(Point& original) : Point(original.get_x(), original.get_y())
{

}

Point::Point() : Point(0, 0)
{

}

float Point::get_x()
{
	return x;
}

float Point::get_y()
{
	return y;
}

int Point::int_x()
{
	return (int) (x + 0.5);
}

int Point::int_y()
{
	return (int) (y + 0.5);
}

float Point::dist(Point& that)
{
	return sqrt((x - that.x) * (x - that.x) + (y - that.y) * (y - that.y));
}

void Point::rotate_around(float x, float y, float phi)
{
    float cos_phi = cos(phi);
    float sin_phi = sin(phi);

    this->x = cos_phi * (this->x - x) - sin_phi * (this->y - y) + x;
    this->y = sin_phi * (this->x - x) + cos_phi * (this->y - y) + y;
}

float Point::dir(Point& that)
{
	return atan2(that.y - y, that.x - x);
}

void Point::shift(float dx, float dy)
{
	x += dx;
	y += dy;
}