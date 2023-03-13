#include "Cell.hpp"
#include <iostream>

Cell::Cell() : _id(-1), _value(-1), _seen(false), _wallLeft(true), _wallUp(true) {
	//std::cout <<  "Cell #id : " << _id << " is born" << std::endl;
}

Cell::Cell(int id, int value, bool seen, bool wallLeft, bool wallUp) : _id(id),_value(value), _seen(seen), _wallLeft(wallLeft), _wallUp(wallUp) {
	//std::cout <<  "Cell #id : " << _id << " is born" << std::endl;
}

Cell::~Cell() {
	//std::cout <<  "Cell #id : " << _id << " is dead" << std::endl;
}

int		Cell::getvalue() {
	return (_value);
}

bool	Cell::getseen() {
	return (_seen);
}

bool	Cell::getwallLeft() {
	return (_wallLeft);
}

bool	Cell::getwallUp() {
	return (_wallUp);
}

void	Cell::setvalue(int value) {
	_value = value;
}

void	Cell::setseen(bool seen) {
	_seen = seen;
}

void	Cell::setwallLeft(bool wall) {
	_wallLeft = wall;
}

void	Cell::setwallUp(bool wall) {
	_wallUp = wall;
}

void	Cell::display() {
	std::cout <<  "Cell #" << this->_id << "(" << this->_value << "), status(" << this->_seen << ") has left wall : " << this->_wallLeft << " and up wall : " << this->_wallUp << "." << std::endl;
}
