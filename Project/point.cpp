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

// todo: this doesn't really work
void Point::rotate_around(float x, float y, float phi)
{
    float cos_phi = cos(phi);
    float sin_phi = sin(phi);

    float new_x = cos_phi * (this->x - x) - sin_phi * (this->y - y) + x;
    float new_y = sin_phi * (this->x - x) + cos_phi * (this->y - y) + y;

    // float distance = sqrt((new_x - x) * (new_x - x) + (new_y - y) * (new_y - y));
    // float original_distance = sqrt((this->x - x) * (this->x - x) + (this->y - y) * (this->y - y));
    // if (original_distance - distance != 0) {
    //     new_x = x + (new_x - x) * (original_distance / distance);
    //     new_y = y + (new_y - y) * (original_distance / distance);
    // }

    this->x = new_x;
    this->y = new_y;
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