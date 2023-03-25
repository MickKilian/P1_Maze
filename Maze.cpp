#include "Maze.hpp"

Maze::Maze() {
}

Maze::Maze(int sizex, int sizey) : _sizex(sizex), _sizey(sizey) {
	//std::cout << "A maze of size : " << _sizex << "x" << _sizey << " is being born" << std::endl;
	_mode = 0;
	for (int i = 0; i < sizex * sizey; ++i) {
		_cell.push_back(Cell(i , i, 0, 1, true, true, true, true));
		_dijkstraTable.push_back(Dijkstra(i , 0, -1, -1, -1, -1));
//		_cell[i]._display();
	}
}

Maze::~Maze() {
	//std::cout << "A maze of size : " << _sizex << "x" << _sizey << " is deleted" << std::endl;
}

bool	Maze::getmode(void) {
	return (_mode);
}

void	Maze::setmode(bool mode) {
	_mode = mode;
}

void	Maze::settimer(time_t timer) {
	_timer = timer;
}

void	Maze::create(void) {
	int	k = _sizex * _sizey - 1;
	int	randcell;
	int	randdir;

	srand(time(0));
	while (k) {
		//Maze::_display(-1);
		randcell = rand() % (_sizex * _sizey);
		randdir = rand() % 2;
		if (randdir == 0 && _idToX(randcell) != 0 && _cell[randcell].getValue() != _cell[randcell - 1].getValue()) {
			k--;
			this->_cell[randcell].setNbSeen(0);
			//this->_cell[randcell].setWallLeft(false);
			this->_cell[randcell].setWall(3, false);
			Maze::_changeGroupValue(_max(this->_cell[randcell - 1].getValue(), this->_cell[randcell].getValue()), 
					_min(this->_cell[randcell - 1].getValue(), this->_cell[randcell].getValue()));
		}
		else if (randdir == 1 && _idToY(randcell) != 0 && _cell[randcell].getValue() != _cell[randcell - _sizex].getValue()) {
			k--;
			this->_cell[randcell].setNbSeen(0);
			//this->_cell[randcell].setWallUp(false);
			this->_cell[randcell].setWall(0, false);
			Maze::_changeGroupValue(_max(this->_cell[randcell - _sizex].getValue(), this->_cell[randcell].getValue()), 
					_min(this->_cell[randcell - _sizex].getValue(), this->_cell[randcell].getValue()));
		}
	}
	_fillWalls();
	Maze::_display(-1);
	setmode(1);
}

void	Maze::_display(int id) {
	std::string	colorgrid;
	std::string	colornumbers;
	std::string	truecolorgrid;
	std::string	truecolornumbers;
	time_t		currenttime;

	_player1.setCell(id);
	time(&currenttime);
	_deadborder = difftime(currenttime, _timer) / SHRINK_TIME;
	_borderPosition = difftime(currenttime, _timer) / SHRINK_TIME;
	updateStatus();
	if (_mode)
		colorgrid = GREEN;
	else
		colorgrid = MAGENTA;
	//usleep(MAKE);
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	for (int j = 0; j < _sizey; ++j) {
		std::cout << std::setw(2) << " ";
		for (int i = 0; i < _sizex; ++i) {
			if (_cell[i + j * _sizex].getWall(0) || i < _deadborder || j <= _deadborder || i > _sizex - 1 -_deadborder || j > _sizey - 1 - _deadborder) {
				if (i < _deadborder || j < _deadborder || i > _sizex - 1 -_deadborder || j > _sizey - _deadborder)
					truecolorgrid = BLUE;
				else
					truecolorgrid = colorgrid;
				std::cout << truecolorgrid << std::setw(6) << "______" << RESET;
				std::cout << std::setw(2) << " ";
			}
			else {
				std::cout << std::setw(6) << " ";
				std::cout << std::setw(2) << " ";
			}
		}
		std::cout << std::endl;
		for (int i = 0; i < _sizex; ++i) {
			if (_cell[i + j * _sizex].getWall(3) || i <= _deadborder || j < _deadborder || i > _sizex - 1 -_deadborder || j > _sizey - 1 - _deadborder) {
				if (i < _deadborder || j < _deadborder || i > _sizex -_deadborder || j > _sizey - 1 - _deadborder)
					truecolorgrid = BLUE;
				else
					truecolorgrid = colorgrid;
				std::cout << truecolorgrid << std::setw(2) << "|" << RESET;
			}
			else {
				std::cout << std::setw(2) << " ";
			}
			std::cout << std::setw(6) << " ";
		}
		if (_deadborder)
			truecolorgrid = BLUE;
		else
			truecolorgrid = colorgrid;
		std::cout << truecolorgrid << std::setw(2) << "|" << RESET;
		std::cout << std::endl;
		for (int i = 0; i < _sizex; ++i) {
			if (_mode)
				colornumbers = BOLDYELLOW;
			else
				colornumbers = Maze::_getcolor(_cell[i + j * _sizex].getValue());
			if (_cell[i + j * _sizex].getWall(3) || i <= _deadborder || j < _deadborder || i > _sizex - 1 -_deadborder || j > _sizey - 1 - _deadborder) {
				if (i < _deadborder || j < _deadborder || i > _sizex -_deadborder || j > _sizey - 1 - _deadborder)
					truecolorgrid = BLUE;
				else
					truecolorgrid = colorgrid;
				std::cout << truecolorgrid << std::setw(2) << "|" << RESET;
			}
			else {
				std::cout << std::setw(2) << " ";
			}
			if (id != i + j * _sizex) {
				std::cout << std::setw(1) << " ";
				if (_cell[i + j * _sizex].getNbSeen() > 0 && _cell[i + j * _sizex].getNbSeen() < 4)
					//std::cout << RED << std::setw(3) << "." << RESET;
					std::cout << GREEN << std::setw(3) << "." << RESET;
				else if (_cell[i + j * _sizex].getNbSeen() >= 4)
					//std::cout << BOLDYELLOW << std::setw(2) << _cell[i + j * _sizex].getValue() << RESET;
					std::cout << std::setw(3) << "   ";
				else {
					if (i < _deadborder || j < _deadborder || i > _sizex - 1 -_deadborder || j > _sizey - 1 - _deadborder)
						truecolornumbers = BLUE;
					else
						truecolornumbers = colornumbers;
					if (_cell[i + j * _sizex].getValue() == 0)
						std::cout << truecolornumbers << std::setw(3) << "o" << RESET;
					else
						std::cout << truecolornumbers << std::setw(3) << _cell[i + j * _sizex].getValue() << RESET;
				}
				std::cout << std::setw(2) << " ";
			}
			else {
				std::cout << std::setw(1) << " ";
				std::cout << BOLDRED << std::setw(3) << "^" << RESET;
				std::cout << std::setw(2) << " ";
				//std::cout << MAGENTA << std::setw(6) << "   o  " << RESET;
			}
		}
		if (_deadborder)
			truecolorgrid = BLUE;
		else
			truecolorgrid = colorgrid;
		std::cout << truecolorgrid << std::setw(2) << "|" << RESET;
		if (j == 0)
			std::cout << colorgrid << std::setw(4) << difftime(currenttime, _timer) << " s" << RESET;
		if (_mode && j == 1)
			std::cout << WHITE << std::setw(4) << _player1.getNbCoins() << " point(s)" << RESET;
		std::cout << std::endl;
		for (int i = 0; i < _sizex; ++i) {
			if (_cell[i + j * _sizex].getWall(3) || i <= _deadborder || j < _deadborder || i > _sizex - 1 -_deadborder || j > _sizey - 1 - _deadborder) {
				if (i < _deadborder || j < _deadborder || i > _sizex -_deadborder || j > _sizey - 1 - _deadborder)
					truecolorgrid = BLUE;
				else
					truecolorgrid = colorgrid;
				std::cout << truecolorgrid << std::setw(2) << "|" << RESET;
			}
			else {
				std::cout << std::setw(2) << " ";
			}
			std::cout << std::setw(6) << " ";
		}
		if (_deadborder)
			truecolorgrid = BLUE;
		else
			truecolorgrid = colorgrid;
		std::cout << truecolorgrid << std::setw(2) << "|" << RESET;
		if (_mode && j == 0)
			std::cout << colorgrid << std::setw(4) << _deadborder << " dead borders" << RESET;
		std::cout << std::endl;
	}
	std::cout << std::setw(2) << " ";
	for (int i = 0; i < _sizex; ++i) {
		if (_deadborder)
			truecolorgrid = BLUE;
		else
			truecolorgrid = colorgrid;
		std::cout << truecolorgrid << std::setw(6) << "______" << RESET;
		std::cout << std::setw(2) << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void	Maze::explore(void) {
	int	retid;

	if (SOLVING_ALGO == 0) {
		retid = 0;
		std::cout << "retid : " << retid << std::endl;
		retid = _depthFirstSearch(retid, -1);
		std::cout << "Congratulations, player1 has collected " << _player1.getNbCoins() << " coins." << std::endl;
	}
	else if (SOLVING_ALGO == 1) {
		std::cout << "Starting Dijkstra" << std::endl;
		//std::cout << _dijkstra(0, 0, _sizex * _sizey - 1) << std::endl;
		_dijkstra(0, _sizex - 1);
		readDijkstraPath(0, _sizex - 1);
		usleep(SPEED);
		//resetPath();
		resetDijkstraTable();
		_display(_sizex - 1);
		usleep(SPEED);

		_dijkstra(_sizex - 1, _sizex * _sizey - 1);
		readDijkstraPath(_sizex - 1, _sizex * _sizey - 1);
		usleep(SPEED);
		//resetPath();
		resetDijkstraTable();
		_display(_sizex * _sizey - 1);
		usleep(SPEED);

		_dijkstra(_sizex * _sizey - 1, (_sizex * _sizey) - _sizex);
		readDijkstraPath(_sizex * _sizey - 1, _sizex * _sizey - _sizex);
		usleep(SPEED);
		//resetPath();
		resetDijkstraTable();
		_display(_sizex * _sizey - _sizex);
		usleep(SPEED);

		_dijkstra(_sizex * _sizey - _sizex, 0);
		readDijkstraPath(_sizex * _sizey - _sizex, -1);
	}
	else if (SOLVING_ALGO == 2) {
		borderDijkstra(_player1.getCell(), 1);
		borderDijkstra(_player1.getCell(), 1);
		borderDijkstra(_player1.getCell(), 1);
		borderDijkstra(_player1.getCell(), 1);
	}
}

int	Maze::borderDijkstra(int start, bool rotation) {
	int	end;
	int	middleX;
	int	middleY;
	int	quadrant;	//0: top-left, 1: top-right, 2: bottom-right, 3: bottom-left
	int	mul;
	int	inc;

	middleX = _sizex / 2;
	middleY = _sizey / 2;
	quadrant = (middleY - _idToY(start) < 0) * (2 + (middleX - _idToX(start) > 0)) + (middleY - _idToY(start) > 0) * (middleX - _idToX(start) < 0);
	switch (quadrant) {
		case 0:
			end = rotation * _XYToId(_sizex - 1, _idToY(start)) + !rotation * _XYToId(_idToX(start), _sizey - 1);
			mul = 1;
			inc = rotation + !rotation * _sizex;
			break;
		case 1:
			end = rotation * _XYToId(_idToX(start), _sizey - 1) + !rotation * _XYToId(_sizex - 1, _idToY(start));
			mul = 1;
			inc = rotation * _sizex + !rotation;
			break;
		case 2:
			end = rotation * _XYToId(0, _idToY(start)) + !rotation * _XYToId(_idToX(start), 0);
			mul = -1;
			inc = rotation + !rotation * _sizex;
			break;
		case 3:
			end = rotation * _XYToId(_idToX(start), 0) + !rotation * _XYToId(0, _idToY(start));
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
		_dijkstra(id, id + mul * inc);
		readDijkstraPath(id, id + mul * inc);
		resetDijkstraTable();
		_display(id + mul * inc);
		if (id + mul * inc == end)
			break;
		id += (mul - (mul > 0) + (mul < 0)) * inc;
		mul = (mul > 0) - (mul < 0);
	}
	return 0;
}

int Maze::_dijkstra(int beg, int end, int curNode)
{
	int	adjNode;

	if (curNode == -1) {
		curNode = beg;
		_dijkstraTable[beg].setF(0);;
	}
	// procedure based on Dijkstra algorithm to find shortest path between beg and end
	// fill dijkstra table until end node is found
	if (curNode != end) {
		for (int dir = 0; dir < 4; ++dir) {
					if (!_cell[curNode].getWall(dir % 4)) {
						adjNode = _getIdWithDir(curNode, dir % 4);
						_addToDijkstraTable(curNode, adjNode);
					}
		}
		_dijkstraTable[curNode].setStatus(1);
		_dijkstra(beg, end, _findNextNodeToDijkstraVisit());
	}
	return (countDijkstraPath(beg, end));
}

int		Maze::_findNextNodeToDijkstraVisit() {
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

void	Maze::_addToDijkstraTable(int curNode, int adjNode) {
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

void	Maze::readDijkstraPath(int beg, int curNode) {
	if (curNode != beg) {
		readDijkstraPath(beg, _dijkstraTable[curNode].getPreviousNode());
		if (_cell[curNode].getNbSeen() == 0)
			_player1.setNbCoins(_player1.getNbCoins() + 1);
		_cell[curNode].setNbSeen(4);
	}
	if (_cell[curNode].getNbSeen() == 0)
		_player1.setNbCoins(_player1.getNbCoins() + 1);
	_cell[curNode].setNbSeen(4);
	usleep(SPEED);
	_display(curNode);
}

void	Maze::resetPath() {
	for (int i = 0; i < _sizex * _sizey; ++i) {
		_cell[i].setNbSeen(0);
	}
}

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

int	Maze::_depthFirstSearch(int id, int fromdir) {
	//time_t		currenttime;
	bool		cont = true;
	int			lastid = 0;

	//time(&currenttime);
	//_deadborder = difftime(currenttime, _timer) / SHRINK_TIME;
	//_borderPosition = difftime(currenttime, _timer) / SHRINK_TIME;
	_cell[id].setNbSeen(_cell[id].getNbSeen() + 1);
	if (_cell[id].getNbSeen() == 1)
		_player1.setNbCoins(_player1.getNbCoins() + 1);
	_display(id);
	usleep(SPEED);
	while (cont) {
		for (int dir = 1; dir < 5; ++dir) {
			if (isInAllowedMaze(id) && isInAllowedMaze(_getIdWithDir(id, dir % 4)) && fromdir != (dir % 4) && !_cell[id].getWall(dir % 4)) {
				_depthFirstSearch(_getIdWithDir(id, dir % 4), (dir + 2) % 4);
				if (!isInAllowedMaze(id)) {
					lastid = id;
					cont = false;
					break;
				}
				_cell[id].setNbSeen(_cell[id].getNbSeen() + 1);
				_display(id);
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

/*int		Maze::isInAllowedMaze(int id) {
	if (_idToY(id) >= _deadborder && _idToX(id) <= _sizex - 1 -_deadborder && _idToY(id) <= _sizey - 1 - _deadborder && _idToX(id) >= _deadborder)
		return (1);
	else
		return (0);
}*/

int		Maze::isInAllowedMaze(int id) {
	updateStatus();
	if (_cell[id].getStatus())
		return (1);
	else
		return (0);
}

int		Maze::updateStatus() {
	for (int id = 0; id < _sizex * _sizey; ++id) {
		if (_idToX(id) + 1 < _borderPosition || _sizex - _idToX(id) < _borderPosition || _idToY(id) + 1 < _borderPosition || _sizey - _idToY(id) < _borderPosition)
			this->_cell[id].setStatus(0);
		else
			this->_cell[id].setStatus(1);
	}
	return (0);
}

int		Maze::_getIdWithDir(int id, int dir) {
	// find id on adjacent node depending on direction:
	// 0. up
	// 1. right
	// 2. down
	// 3. left
	switch (dir) {
		case 0:
			return (id - _sizex);
			break;
		case 1:
			return (id + 1);
			break;
		case 2:
			return (id + _sizex);
			break;
		case 3:
			return (id - 1);
			break;
		default:
			return (-1);
	}
}

int		Maze::_finDirWithId(int from, int to) {
	if (to == from - _sizex)
		return (0);
	else if (to == from + 1)
		return (1);
	else if (to == from + _sizex)
		return (2);
	else if (to == from - 1)
		return (3);
	else
		return (-1);
}

int		Maze::_idToX(int id) {
	return (id % _sizex);
}

int		Maze::_idToY(int id) {
	return (id / _sizex);
}

int		Maze::_XYToId(int x, int y) {
	return (x + y * _sizex);
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
		if (_idToX(id) < _sizex - 1)
			_cell[id].setWall(1, _cell[id + 1].getWall(3));
		else
			_cell[id].setWall(1, true);
		if (_idToY(id) < _sizey - 1)
			_cell[id].setWall(2, _cell[id + _sizex].getWall(0));
		else
			_cell[id].setWall(2, true);
	}
}

Maze*	newMaze(int sizex, int sizey) {
	Maze*	newMaze = new Maze(sizex, sizey);
	
	return  (newMaze);
}

std::string	Maze::_getcolor(int nb) {
	int	k = nb % 7;

	switch (k) {
		case 0:
			return (MAGENTA);
			break;
		case 1:
			return (GREEN);
			break;
		case 2:
			return (YELLOW);
			break;
		case 3:
			return (BLUE);
			break;
		case 4:
			return (RED);
			break;
		case 5:
			return (CYAN);
			break;
		case 6:
			return (WHITE);
			break;
		default:
			return (MAGENTA);
	}
}

int	Maze::_min(int a, int b) {
	if (a < b)
		return (a);
	else
		return (b);
}

int Maze::_max(int a, int b) {
	if (a > b)
		return (a);
	else
		return (b);
}
