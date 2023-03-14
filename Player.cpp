#include "Player.hpp"
#include <iostream>

Player::Player() : _name("player"), _id(0), _cell(0), _nbcoins(0), _lives(0), _mode(0), _speed(1), _strategy(1) {
}

Player::Player(std::string name, int id, int cell, int nbcoins, int lives, int mode, int speed, int strategy) : _name(name), _id(id), _cell(cell),
	_nbcoins(nbcoins), _lives(lives), _mode(mode), _speed(speed), _strategy(strategy) {
}

Player::~Player() {
}

std::string	Player::getname() {
	return (_name);
}

int	Player::getid() {
	return (_id);
}

int	Player::getcell() {
	return (_cell);
}

int	Player::getnbcoins() {
	return (_nbcoins);
}

int	Player::getlives() {
	return (_lives);
}

int	Player::getmode() {
	return (_mode);
}

int	Player::getspeed() {
	return (_speed);
}

int	Player::getstrategy() {
	return (_strategy);
}

void	Player::setcell(int cell) {
	_cell = cell;
}

void	Player::setid(int id) {
	_id = id;
}

void	Player::setnbcoins(int nbcoins) {
	_nbcoins = nbcoins;
}

void	Player::setlives(int lives) {
	_lives =lives;
}

void	Player::setmode(int mode) {
	_mode = mode;
}

void	Player::setspeed(int speed) {
	_speed = speed;
}

void	Player::setstrategy(int strategy) {
	_strategy = strategy;
}

void	Player::display() {
	std::cout <<  "Player #" << this->_id << "(" << this->_name <<
		") - nbpoints(" << this->_nbcoins <<
		"), lives( " << this->_lives <<
		"), speed( " << this->_speed <<
		std::endl;
}
