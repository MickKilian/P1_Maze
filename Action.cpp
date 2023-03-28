#include "Action.hpp"

Action::Action() {
}

Action::Action(Point position, double orientation, Point target, double maxSpeed,
		bool forceForward, double tolerance) : _position(position), _orientation(orientation),
	_target(target), _maxSpeed(maxSpeed), _forceForward(forceForward), _tolerance(tolerance) {
}

Action::~Action() {
}

double	Action::getNewOrientation() {
	return (_newOrientation);
}

double	Action::getMaxSpeed() {
	return(_maxSpeed);
}

double	Action::getAngleTurn() {
	return(_angleTurn);
}

double	Action::getTransGo() {
	return(_transGo);
}

void	Action::setTarget(Point target) {
	_target = target;
}

void	Action::setPosition(Point point) {
	_position = point;
}

void	Action::setOrientation(double angle) {
	_orientation = angle;
}

void	Action::setNewOrientation(double angle) {
	_newOrientation = angle;
}

void	Action::setAngleTurn(double angle) {
	_angleTurn = angle;
}

void	Action::setTransGo(double dist) {
	_transGo = dist;
}

void	Action::decision(Point point) {
	double	angle;
	double	dist;

	setTarget(point);
	if (Utils::samePoints(_position, _target, _tolerance)) {
		angle = 0;
		dist = 0;
		setNewOrientation(_orientation);
	}
	else {
		angle = Utils::modulo360(Utils::abAngle(_position, _target) - _orientation);
		dist = Utils::dist(_position, _target);
		if (!_forceForward && std::abs(angle) > 90) {
				angle = Utils::modulo360(angle - 180);
				dist = -dist;
		}
	}
	setAngleTurn(angle);
	setNewOrientation(Utils::modulo360(_orientation + angle));
	setTransGo(dist);
}

void	Action::turn(double deg, double speed) {
	std::cout << "I am turing : " << deg << "deg with speed " << speed << "m/s" << std::endl;
}

void	Action::go(double dist, double speed) {
	std::cout << "I am rolling : " << dist << "mm with speed " << speed << "m/s" << std::endl;
}

void	Action::display() {
	std::cout << "turn : " << std::setw(7) << getAngleTurn() << std::setw(7) << getTransGo() << std::setw(7) << getNewOrientation();
}
