#include "Dijkstra.hpp"
#include <iostream>

		int		_id;
		int		_status;
		int		_f;
		int		_g;
		int		_h;
		int		_previousNode;
Dijkstra::Dijkstra() : _id(-1), _status(-1), _f(-1), _g(-1), _h(-1), _previousNode(-1) {
}

Dijkstra::Dijkstra(int id, int status, int f, int g, int h, int previousNode) : _id(id), _status(status),
	_f(f), _g(g), _h(h), _previousNode(previousNode) {
}

Dijkstra::~Dijkstra() {
}

int	Dijkstra::getId() {
	return (_id);
}

int	Dijkstra::getStatus() {
	return (_status);
}

int	Dijkstra::getF() {
	return (_f);
}

int	Dijkstra::getG() {
	return (_g);
}

int	Dijkstra::getH() {
	return (_h);
}

int	Dijkstra::getPreviousNode() {
	return (_previousNode);
}

void	Dijkstra::setId(int id) {
	_id = id;
}

void	Dijkstra::setStatus(int status) {
	_status = status;
}

void	Dijkstra::setF(int value) {
	_f = value;
}

void	Dijkstra::setG(int value) {
	_g = value;
}

void	Dijkstra::setH(int value) {
	_h = value;
}

void	Dijkstra::setPreviousNode(int id) {
	_previousNode = id;
}
