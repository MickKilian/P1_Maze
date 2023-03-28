#include "Point.hpp"

Point::Point() {
}

Point::Point(double x, double y) : _x(x), _y(y) {
}

Point::~Point() {
}

double	Point::getX() {
	return (_x);
}

double	Point::getY() {
	return (_y);
}

void	Point::setX(double x) {
	_x = x;
}

void	Point::setY(double y) {
	_y = y;
}

void	Point::display() {
	std::cout << "(" << std::setw(4) << getX() << ", " << std::setw(4) << getY() << ")";
}
