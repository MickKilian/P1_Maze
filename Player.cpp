#include "Player.hpp"

Player::Player() : _name("player"), _id(0), _cell(0), _nbcoins(0), _lives(0), _mode(0), _speed(1), _strategy(1) {
}

Player::Player(std::string name, int id, int cell, int nbcoins, int lives, int mode, int speed, int strategy) : _name(name), _id(id), _cell(cell),
	_nbcoins(nbcoins), _lives(lives), _mode(mode), _speed(speed), _strategy(strategy) {
}

Player::~Player() {
}

std::string	Player::getName() {
	return (_name);
}

double	Player::getX() {
	return (_x);
}

double	Player::getY() {
	return (_y);
}

int	Player::getId() {
	return (_id);
}

int	Player::getCell() {
	return (_cell);
}

int	Player::getNbCoins() {
	return (_nbcoins);
}

int	Player::getLives() {
	return (_lives);
}

int	Player::getMode() {
	return (_mode);
}

int	Player::getSpeed() {
	return (_speed);
}

int	Player::getStrategy() {
	return (_strategy);
}

void	Player::setCell(int cell) {
	_cell = cell;
}

void	Player::setX(double x) {
	_x = x;
}

void	Player::setY(double y) {
	_y = y;
}

void	Player::setId(int id) {
	_id = id;
}

void	Player::setNbCoins(int nbcoins) {
	_nbcoins = nbcoins;
}

void	Player::setLives(int lives) {
	_lives =lives;
}

void	Player::setMode(int mode) {
	_mode = mode;
}

void	Player::setSpeed(int speed) {
	_speed = speed;
}

void	Player::setStrategy(int strategy) {
	_strategy = strategy;
}
