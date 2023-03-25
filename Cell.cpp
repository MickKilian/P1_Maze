#include "Cell.hpp"
#include <iostream>

Cell::Cell() : _id(-1), _value(-1), _nbseen(-1), _status(-1) {
	_wall[0] = true;
	_wall[1] = true;
	_wall[2] = true;
	_wall[3] = true;
}

Cell::Cell(int id, int value, int nb, int status, bool wall0, bool wall1, bool wall2, bool wall3) :
	_id(id),_value(value), _nbseen(nb), _status(status) {
		_wall[0] = wall0;
		_wall[1] = wall1;
		_wall[2] = wall2;
		_wall[3] = wall3;
}

Cell::~Cell() {
}

int		Cell::getId() {
	return (_id);
}

int		Cell::getValue() {
	return (_value);
}

int		Cell::getNbSeen() {
	return (_nbseen);
}

int		Cell::getStatus() {
	return (_status);
}

bool	Cell::getWall(int dir) {
	return (_wall[dir]);
}

void	Cell::setId(int id) {
	_id = id;
}

void	Cell::setValue(int value) {
	_value = value;
}

void	Cell::setNbSeen(int nb) {
	_nbseen = nb;
}

void	Cell::setStatus(int status) {
	_status = status;
}

void	Cell::setWall(int dir, bool wall) {
	_wall[dir] = wall;
}
