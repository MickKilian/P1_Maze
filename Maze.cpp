#include "Maze.hpp"

Maze::Maze() {
}

Maze::Maze(int sizex, int sizey) : _sizex(sizex), _sizey(sizey) {
	//std::cout << "A maze of size : " << _sizex << "x" << _sizey << " is being born" << std::endl;
	for (int i = 0; i < sizex * sizey; ++i) {
		_cell.push_back(Cell(i, i, 0, true, true, true, true));
		_dijkstraTable.push_back(Dijkstra(i , 0, -1, -1, -1, -1));
//		_cell[i]._display();
	}
}

Maze::~Maze() {
}

int		Maze::getSizeX(void) {
	return (_sizex);
}

int		Maze::getSizeY(void) {
	return (_sizey);
}

std::vector<Cell>	Maze::getCell(void) {
	return (_cell);
}

Maze	Maze::create(void) {
	int	k = _sizex * _sizey - 1;
	int	randcell;
	int	randdir;

	srand(time(0));
	while (k) {
		randcell = rand() % (_sizex * _sizey);
		randdir = rand() % 2;		//0: LEFT, 1: UP
		if (randdir == 0 && Utils::cellIdToX(randcell, _sizex) != 0 && _cell[randcell].getValue() != _cell[randcell - 1].getValue()) {
			k--;
			//this->_cell[randcell].setNbSeen(0);
			//this->_cell[randcell].setWallLeft(false);
			this->_cell[randcell].setWall(3, false);
			Maze::_changeGroupValue(Utils::max(this->_cell[randcell - 1].getValue(), this->_cell[randcell].getValue()), 
					Utils::min(this->_cell[randcell - 1].getValue(), this->_cell[randcell].getValue()));
		}
		else if (randdir == 1 && Utils::cellIdToY(randcell, _sizex) != 0 && _cell[randcell].getValue() != _cell[randcell - _sizex].getValue()) {
			k--;
			//this->_cell[randcell].setNbSeen(0);
			//this->_cell[randcell].setWallUp(false);
			this->_cell[randcell].setWall(0, false);
			Maze::_changeGroupValue(Utils::max(this->_cell[randcell - _sizex].getValue(), this->_cell[randcell].getValue()), 
					Utils::min(this->_cell[randcell - _sizex].getValue(), this->_cell[randcell].getValue()));
		}
	}
	_fillWalls();
	//Maze::_display(-1);
	return (*this);
}

void	Maze::_changeGroupValue(int oldvalue, int newvalue) {
	for (int i = 0; i < _sizex * _sizey; ++i) {
		if (this->_cell[i].getValue() == oldvalue) {
			this->_cell[i].setValue(newvalue);
		}
	}
}

void	Maze::_fillWalls() {
	for (int id = 0; id < _sizex * _sizey; ++id) {
		if (Utils::cellIdToX(id, _sizex) < _sizex - 1)
			_cell[id].setWall(1, _cell[id + 1].getWall(3));
		else
			_cell[id].setWall(1, true);
		if (Utils::cellIdToY(id, _sizex) < _sizey - 1)
			_cell[id].setWall(2, _cell[id + _sizex].getWall(0));
		else
			_cell[id].setWall(2, true);
	}
}

/*int	Maze::borderDijkstra(int start, bool rotation) {
	int	end;
	int	middleX;
	int	middleY;
	int	quadrant;	//0: top-left, 1: top-right, 2: bottom-right, 3: bottom-left
	int	mul;
	int	inc;

	middleX = _sizex / 2;
	middleY = _sizey / 2;
	quadrant = (middleY - Utils::cellIdToY(start, _sizex) < 0) * (2 + (middleX - Utils::cellIdToX(start, _sizex) > 0)) + (middleY - Utils::cellIdToY(start, _sizex) > 0) * (middleX - Utils::cellIdToX(start, _sizex) < 0);
	switch (quadrant) {
		case 0:
			end = rotation * Utils::xyToCellId(_sizex - 1, Utils::cellIdToY(start, _sizex), _sizex) + !rotation * Utils::xyToCellId(Utils::cellIdToX(start, _sizex), _sizey - 1, _sizex);
			mul = 1;
			inc = rotation + !rotation * _sizex;
			break;
		case 1:
			end = rotation * Utils::xyToCellId(Utils::cellIdToX(start, _sizex), _sizey - 1, _sizex) + !rotation * Utils::xyToCellId(_sizex - 1, Utils::cellIdToY(start, _sizex), _sizex);
			mul = 1;
			inc = rotation * _sizex + !rotation;
			break;
		case 2:
			end = rotation * Utils::xyToCellId(0, Utils::cellIdToY(start, _sizex), _sizex) + !rotation * Utils::xyToCellId(Utils::cellIdToX(start, _sizex), 0, _sizex);
			mul = -1;
			inc = rotation + !rotation * _sizex;
			break;
		case 3:
			end = rotation * Utils::xyToCellId(Utils::cellIdToX(start, _sizex), 0, _sizex) + !rotation * Utils::xyToCellId(0, Utils::cellIdToY(start, _sizex), _sizex);
			mul = -1;
			inc = rotation * _sizex + !rotation;
			break;
	}
	for (int id = start; mul * id < mul * end; id += ((mul > 0) - (mul < 0)) * inc) {
		while (mul * (id + mul * inc) < mul * end && _cell[id + mul * inc].getNbSeen() == 4) {
			mul = mul + (mul > 0) - (mul < 0);
		}
		if (id + mul * inc == end && _cell[id + mul * inc].getNbSeen() == 4)
			break;
		dijkstra(id, id + mul * inc);
		readDijkstraPath(id, id + mul * inc);
		resetDijkstraTable();
		////_display(id + mul * inc);
		if (id + mul * inc == end)
			break;
		id += (mul - (mul > 0) + (mul < 0)) * inc;
		mul = (mul > 0) - (mul < 0);
	}
	return 0;
}*/

int Maze::dijkstra(int beg, int end, int curNode)
{
	int	adjNode;

	if (curNode == -1) {
		curNode = beg;
		_dijkstraTable[beg].setF(0);;
	}
	// procedure based on Dijkstra algorithm to find shortest path between beg and end
	// fill dijkstra table until end node is found
	if (curNode != end) {
		//std::cout << "curNode : " << curNode << std::endl;
		for (int dir = 0; dir < 4; ++dir) {
			//std::cout << "   dir : " << dir << ", wall : " << _cell[curNode].getWall(dir % 4) << std::endl;
			if (!_cell[curNode].getWall(dir % 4)) {
				adjNode = Utils::getIdWithDir(curNode, dir % 4, _sizex);
				//std::cout << "      adjNode : " << adjNode << std::endl;
				addToDijkstraTable(curNode, adjNode);
			}
		}
		_dijkstraTable[curNode].setStatus(1);
		dijkstra(beg, end, findNextNodeToDijkstraVisit());
	}
	return (countDijkstraPath(beg, end));
}

int		Maze::findNextNodeToDijkstraVisit() {
	int	min = -1;
	int	ret = -1;

	for (int i = 0; i < _sizex * _sizey; ++i) {
		if ((min == -1 && !_dijkstraTable[i].getStatus()) || (!_dijkstraTable[i].getStatus() && _dijkstraTable[i].getF() != -1 && _dijkstraTable[i].getF() < min)) {
			min = _dijkstraTable[i].getF();
			ret = i;
		}
	}
	return (ret);
}

void	Maze::addToDijkstraTable(int curNode, int adjNode) {
	int	g = _dijkstraTable[curNode].getF();

	if (_dijkstraTable[adjNode].getF() == -1 || _dijkstraTable[adjNode].getF() > g + 1) {
		_dijkstraTable[adjNode].setF(g + 1);
		_dijkstraTable[adjNode].setPreviousNode(curNode);
	}
}

void	Maze::displayDijkstraTable() {
	for (int i = 0; i < _sizex * _sizey; ++i) {
		std::cout << std::setw(7) << _dijkstraTable[i].getId();
		std::cout << std::setw(7) << _dijkstraTable[i].getStatus();
		std::cout << std::setw(7) << _dijkstraTable[i].getF();
		std::cout << std::setw(7) << _dijkstraTable[i].getPreviousNode();
		std::cout << std::endl;
	}
}

int	Maze::countDijkstraPath(int beg, int curNode) {
	if (curNode == beg)
		return (0);
	else
		return (1 + countDijkstraPath(beg, _dijkstraTable[curNode].getPreviousNode()));
}

Route	Maze::readDijkstraPath(int beg, int curNode, Route route) {
	if (curNode != beg) {
		readDijkstraPath(beg, _dijkstraTable[curNode].getPreviousNode(), route);
		if (_cell[curNode].getNbSeen() == 0)
			_nbCollectedCoins++;
		_cell[curNode].setNbSeen(4);
	}
	if (_cell[curNode].getNbSeen() == 0)
		_nbCollectedCoins++;
	_cell[curNode].setNbSeen(4);
	std::cout << curNode << ", ";
	route.getCell().push_back(curNode);
	std::cout << "route : " << route.getCell()[0] << ", ";
	//usleep(SPEED);
	////_display(curNode);
	return (route);
}

/*void	Maze::resetPath() {
	for (int i = 0; i < _sizex * _sizey; ++i) {
		_cell[i].setNbSeen(0);
	}
}*/

void	Maze::resetDijkstraTable() {
	for (int i = 0; i < _sizex * _sizey; ++i) {
		_dijkstraTable[i].setId(i);
		_dijkstraTable[i].setStatus(0);
		_dijkstraTable[i].setF(-1);
		_dijkstraTable[i].setG(-1);
		_dijkstraTable[i].setH(-1);
		_dijkstraTable[i].setPreviousNode(-1);
	}
}

/*int	Maze::depthFirstSearch(int id, int fromdir) {
	//time_t		currenttime;
	bool		cont = true;
	int			lastid = 0;

	//time(&currenttime);
	//_deadborder = difftime(currenttime, _timer) / SHRINK_TIME;
	//_borderPosition = difftime(currenttime, _timer) / SHRINK_TIME;
	_cell[id].setNbSeen(_cell[id].getNbSeen() + 1);
	if (_cell[id].getNbSeen() == 1)
		_nbCollectedCoins++;
	////_display(id);
	usleep(SPEED);
	while (cont) {
		for (int dir = 1; dir < 5; ++dir) {
			if (isInAllowedMaze(id) && isInAllowedMaze(Utils::getIdWithDir(id, dir % 4, _sizex)) && fromdir != (dir % 4) && !_cell[id].getWall(dir % 4)) {
				depthFirstSearch(Utils::getIdWithDir(id, dir % 4, _sizex), (dir + 2) % 4);
				if (!isInAllowedMaze(id)) {
					lastid = id;
					cont = false;
					break;
				}
				_cell[id].setNbSeen(_cell[id].getNbSeen() + 1);
				////_display(id);
				usleep(SPEED);
			}
		}
		//_display(_getIdWithDir(id, fromdir));
		if (cont == true)
			_cell[id].setNbSeen(4);
		cont = false;
	}
	return (lastid);
}

int	Maze::depthFirstSearch(int fromdir, int id) {
	//id is optional in this function
	//time_t		currenttime;
	bool		cont = true;
	int			lastid = 0;

	//time(&currenttime);
	//_deadBorder = difftime(currenttime, _timer) / SHRINK_SPEED;
	//_borderPosition = difftime(currenttime, _timer) / SHRINK_SPEED;
	_cell[id].setNbSeen(_cell[id].getNbSeen() + 1);
	if (_cell[id].getNbSeen() == 1)
		_player1.setNbCoins(_player1.getNbCoins() + 1);
	_display(id);
	usleep(Game->player[0].getMovingSpeedRate() * MAX_SPEED);
	while (cont) {
		for (int dir = 1; dir < 5; ++dir) {
			if (isInAllowedMaze(id) && isInAllowedMaze(_getIdWithDir(id, dir % 4)) && fromdir != (dir % 4) && !_cell[id].getWall(dir % 4)) {
				depthFirstSearch(_getIdWithDir(dir % 4, dir), (dir + 2) % 4);
				if (!isInAllowedMaze(id)) {
					lastid = id;
					cont = false;
					break;
				}
				_cell[id].setNbSeen(_cell[id].getNbSeen() + 1);
				_display(id);
				usleep(Game->player[0].getMovingSpeedRate() * MAX_SPEED);
			}
		}
		//_display(_getIdWithDir(id, fromdir));
		if (cont == true)
			_cell[id].setNbSeen(4);
		cont = false;
	}
	return (lastid);
}*/
