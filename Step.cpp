#include "Step.hpp"

Step::Step() {
}

Step::Step(Point point, double angle, double speed, time_t time) :
	_point(point), _orientation(angle), _speed(speed), _time(time) {
}

Step::~Step() {
}

Point	Step::getPoint() {
	return (_point);
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

void	Step::setPoint(Point point) {
	_point = point;
}
