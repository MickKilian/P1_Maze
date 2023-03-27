#include "Player.hpp"

Player::Player() : _id(-1), _type(-1), _x(-1), _y(-1), _orientation(0),
	_nbcoins(0), _lives(0), _movingSpeedRate(1), _maxSpeed(1), _strategy(1),
	_sizeX(0), _sizeY(0) {
	_route.getCell().push_back(0);
	std::cout << "A route zith first cell : " << 0 << " was created." << std::endl;
}

Player::Player(int id, int type, double x, double y, double orientation,
	int nbcoins, int lives, int movingSpeedRate, int maxSpeed, int strategy,
	int startingCell, int sizeX, int sizeY) :
	_id(id), _type(type), _x(x), _y(y), _orientation(orientation),
	_nbcoins(nbcoins), _lives(lives), _movingSpeedRate(movingSpeedRate), _maxSpeed(maxSpeed),
	_strategy(strategy), _startingCell(startingCell), _sizeX(sizeX), _sizeY (sizeY), _route() {
	_route.getCell().push_back(startingCell);
}

Player::~Player() {
}

int	Player::getId() {
	return (_id);
}

int	Player::getType() {
	return (_type);
}

double	Player::getX() {
	return (_x);
}

double	Player::getY() {
	return (_y);
}

double	Player::getOrientation() {
	return (_orientation);
}

//int	Player::getCell() {
//	return (_cell);
//}

int	Player::getNbCoins() {
	return (_nbcoins);
}

int	Player::getLives() {
	return (_lives);
}

//int	Player::getMode() {
//	return (_mode);
//}

int	Player::getMovingSpeedRate() {
	return (_movingSpeedRate);
}

int	Player::getMaxSpeed() {
	return (_maxSpeed);
}

int	Player::getStrategy() {
	return (_strategy);
}

int	Player::getStartingCell() {
	return (_startingCell);
}

int	Player::getSizeX() {
	return (_sizeX);
}

int	Player::getSizeY() {
	return (_sizeY);
}

Route	Player::getRoute() {
	return (_route);
}

void	Player::setId(int id) {
	_id = id;
}

void	Player::setType(int type) {
	_type = type;
}

void	Player::setX(double x) {
	_x = x;
}

void	Player::setY(double y) {
	_y = y;
}

void	Player::setOrientation(double orientation) {
	_orientation = orientation;
}

//void	Player::setCell(int cell) {
//	_cell = cell;
//}

void	Player::setNbCoins(int nbcoins) {
	_nbcoins = nbcoins;
}

void	Player::setLives(int lives) {
	_lives =lives;
}

//void	Player::setMode(int mode) {
//	_mode = mode;
//}

void	Player::setMovingSpeedRate(int speed) {
	_movingSpeedRate = speed;
}

void	Player::setMaxSpeed(int maxSpeed) {
	_maxSpeed = maxSpeed;
}

void	Player::setStrategy(int strategy) {
	_strategy = strategy;
}

void	Player::setRoute(Route route) {
	_route = route;
}
