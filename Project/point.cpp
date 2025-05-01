#include "point.h"

Point::Point(double new_x, double new_y) : x(new_x), y(new_y)
{

}


Point::Point(Point& original) : Point(original.get_x(), original.get_y())
{

}

Point::Point() : Point(0, 0)
{

}

double Point::get_x()
{
	return x;
}

double Point::get_y()
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

double Point::dist(Point& that)
{
	return sqrt((x - that.x) * (x - that.x) + (y - that.y) * (y - that.y));
}

double Point::dir(Point& that)
{
	return atan2(that.y - y, that.x - x);
}

void Point::shift(double dx, double dy)
{
	x += dx;
	y += dy;
}