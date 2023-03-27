#include "Step.hpp"

Step::Step() {
}

Step::Step(double x, double y, double angle, double speed, time_t time) :
	_x(x), _y(y), _orientation(angle), _speed(speed), _time(time) {
}

Step::~Step() {
}

double	Step::getX() {
	return (_x);
}

double	Step::getY() {
	return (_y);
}

double	Step::getOrientation() {
	return (_orientation);
}

double	Step::getSpeed() {
	return (_speed);
}

int	Step::getTime() {
	return (_time);
}
