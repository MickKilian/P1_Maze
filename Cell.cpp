#include "Cell.hpp"
#include <iostream>

Cell::Cell() : _id(-1), _value(-1), _nbseen(-1), _wallLeft(true), _wallUp(true) {
}

Cell::Cell(int id, int value, int nb, bool wallLeft, bool wallUp) : _id(id),_value(value), _nbseen(nb), _wallLeft(wallLeft), _wallUp(wallUp) {
}

Cell::~Cell() {
}

int		Cell::getvalue() {
	return (_value);
}

int		Cell::getnbseen() {
	return (_nbseen);
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

void	Cell::setnbseen(int nb) {
	_nbseen = nb;
}

void	Cell::setwallLeft(bool wall) {
	_wallLeft = wall;
}

void	Cell::setwallUp(bool wall) {
	_wallUp = wall;
}

void	Cell::display() {
	std::cout <<  "Cell #" << this->_id << "(" << this->_value << "), status(" << this->_nbseen << ") has left wall : " << this->_wallLeft << " and up wall : " << this->_wallUp << "." << std::endl;
}
