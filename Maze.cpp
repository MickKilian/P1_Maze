#include "Maze.hpp"

Maze::Maze() {
}

Maze::Maze(int sizex, int sizey) : _sizex(sizex), _sizey(sizey) {
	//std::cout << "A maze of size : " << _sizex << "x" << _sizey << " is being born" << std::endl;
	_mode = 0;
	for (int i = 0; i < sizex * sizey; ++i) {
		_content.push_back(Cell(i , i, false, true, true));
		_dijkstraTable.push_back(Dijkstra(i , 0, -1, -1, -1, -1));
//		_content[i]._display();
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
		if (randdir == 0 && _idToX(randcell) != 0 && _content[randcell].getvalue() != _content[randcell - 1].getvalue()) {
			k--;
			this->_content[randcell].setnbseen(0);
			this->_content[randcell].setwallLeft(false);
			Maze::_changegroupvalue(_max(this->_content[randcell - 1].getvalue(), this->_content[randcell].getvalue()), 
					_min(this->_content[randcell - 1].getvalue(), this->_content[randcell].getvalue()));
		}
		else if (randdir == 1 && _idToY(randcell) != 0 && _content[randcell].getvalue() != _content[randcell - _sizex].getvalue()) {
			k--;
			this->_content[randcell].setnbseen(0);
			this->_content[randcell].setwallUp(false);
			Maze::_changegroupvalue(_max(this->_content[randcell - _sizex].getvalue(), this->_content[randcell].getvalue()), 
					_min(this->_content[randcell - _sizex].getvalue(), this->_content[randcell].getvalue()));
		}
	}
	Maze::_display(-1);
	setmode(1);
}

void	Maze::_display(int id) {
	std::string	colorgrid;
	std::string	colornumbers;
	std::string	truecolorgrid;
	std::string	truecolornumbers;
	time_t		currenttime;

	time(&currenttime);
	if (_mode)
		colorgrid = GREEN;
	else
		colorgrid = MAGENTA;
	usleep(MAKE);
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	for (int j = 0; j < _sizey; ++j) {
		std::cout << std::setw(2) << " ";
		for (int i = 0; i < _sizex; ++i) {
			if (_content[i + j * _sizex].getwallUp() || i < _deadborder || j <= _deadborder || i > _sizex - 1 -_deadborder || j > _sizey - 1 - _deadborder) {
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
			if (_content[i + j * _sizex].getwallLeft() || i <= _deadborder || j < _deadborder || i > _sizex - 1 -_deadborder || j > _sizey - 1 - _deadborder) {
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
				colornumbers = Maze::_getcolor(_content[i + j * _sizex].getvalue());
			if (_content[i + j * _sizex].getwallLeft() || i <= _deadborder || j < _deadborder || i > _sizex - 1 -_deadborder || j > _sizey - 1 - _deadborder) {
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
				if (_content[i + j * _sizex].getnbseen() > 0 && _content[i + j * _sizex].getnbseen() < 4)
					//std::cout << RED << std::setw(3) << "." << RESET;
					std::cout << GREEN << std::setw(3) << "." << RESET;
				else if (_content[i + j * _sizex].getnbseen() >= 4)
					//std::cout << BOLDYELLOW << std::setw(2) << _content[i + j * _sizex].getvalue() << RESET;
					std::cout << std::setw(3) << "   ";
				else {
					if (i < _deadborder || j < _deadborder || i > _sizex - 1 -_deadborder || j > _sizey - 1 - _deadborder)
						truecolornumbers = BLUE;
					else
						truecolornumbers = colornumbers;
					if (_content[i + j * _sizex].getvalue() == 0)
						std::cout << truecolornumbers << std::setw(3) << "o" << RESET;
					else
						std::cout << truecolornumbers << std::setw(3) << _content[i + j * _sizex].getvalue() << RESET;
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
			std::cout << WHITE << std::setw(4) << _player1.getnbcoins() << " point(s)" << RESET;
		std::cout << std::endl;
		for (int i = 0; i < _sizex; ++i) {
			if (_content[i + j * _sizex].getwallLeft() || i <= _deadborder || j < _deadborder || i > _sizex - 1 -_deadborder || j > _sizey - 1 - _deadborder) {
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
	/*int	retid;

	retid = 0;
	while (1) {
		std::cout << "retid : " << retid << std::endl;
		retid = _depthFirstSearch(retid, -1);
	}
	std::cout << "Congratulations, player1 has collected " << _player1.getnbcoins() << " coins." << std::endl;
	*/
	//std::cout << "Starting Dijkstra" << std::endl;
	//std::cout << _dijkstra(0, 0, _sizex * _sizey - 1) << std::endl;

	_dijkstra(0, 0, _sizex - 1);
	readDijkstraPath(0, _sizex - 1);
	usleep(1000000);
	resetPath();
	resetDijkstraTable();
	_display(_sizex - 1);
	usleep(1000000);

	_dijkstra(_sizex - 1, _sizex - 1, _sizex * _sizey - 1);
	readDijkstraPath(_sizex - 1, _sizex * _sizey - 1);
	usleep(1000000);
	resetPath();
	resetDijkstraTable();
	_display(_sizex * _sizey - 1);
	usleep(1000000);

	_dijkstra(_sizex * _sizey - 1, _sizex * _sizey - 1, (_sizex * _sizey) - _sizex);
	readDijkstraPath(_sizex * _sizey - 1, _sizex * _sizey - _sizex);
	usleep(1000000);
	resetPath();
	resetDijkstraTable();
	_display(_sizex * _sizey - _sizex);
	usleep(1000000);

	_dijkstra(_sizex * _sizey - _sizex, _sizex * _sizey - _sizex, 0);
	readDijkstraPath(_sizex * _sizey - _sizex, -1);
}

int Maze::_dijkstra(int beg, int curNode, int end)
{
	int	adjNode;

	if (beg == curNode)
		_dijkstraTable[beg].setF(0);;
	// procedure based on Dijkstra algorithm to find shortest path between beg and end
	// fill dijkstra table until end node is found
	/*
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << "current node : " << curNode << std::endl << std::endl;;
	displayDijkstraTable();
	*/
	//_content[curNode].setnbseen(_content[curNode].getnbseen() + 1);
	//_display(curNode);
	if (curNode != end) {
		//usleep (1000000);
		// try UP
					if (!_content[curNode].getwallUp()) {
						adjNode = _getidwithdir(curNode, 0);
						_addToDijkstraTable(curNode, adjNode);
					}
		// try RIGHT
					if ((_idToX(curNode) != _sizex - 1) && !_content[_getidwithdir(curNode, 1)].getwallLeft()) {
						adjNode = _getidwithdir(curNode, 1);
						_addToDijkstraTable(curNode, adjNode);
					}
		// try DOWN
					if ((_idToY(curNode) != _sizey - 1) && !_content[_getidwithdir(curNode, 2)].getwallUp()) {
						adjNode = _getidwithdir(curNode, 2);
						_addToDijkstraTable(curNode, adjNode);
					}
		// try LEFT
					if (!_content[curNode].getwallLeft()) {
						adjNode = _getidwithdir(curNode, 3);
						_addToDijkstraTable(curNode, adjNode);
					}
		_dijkstraTable[curNode].setStatus(1);
		//std::cout << std::endl;
		_dijkstra(beg, _findNextNodeToDijkstraVisit(), end);
	}
	return (0);
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

	//std::cout << "adjacent node : " << adjNode << std::endl;
	//std::cout << "   previous f value : " << _dijkstraTable[adjNode].getF() << std::endl;
	if (_dijkstraTable[adjNode].getF() == -1 || _dijkstraTable[adjNode].getF() > g + 1) {
		_dijkstraTable[adjNode].setF(g + 1);
		_dijkstraTable[adjNode].setPreviousNode(curNode);
	}
	//std::cout << "   new f value : " << _dijkstraTable[adjNode].getF() << std::endl;
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

void	Maze::readDijkstraPath(int beg, int end) {
	int	curNode = end;

	while (curNode != beg) {
		_content[curNode].setnbseen(_content[curNode].getnbseen() + 1);
		_display(curNode);
		usleep(SPEED);
		curNode = _dijkstraTable[curNode].getPreviousNode();
	}
	_display(curNode);
}

void	Maze::resetPath() {
	for (int i = 0; i < _sizex * _sizey; ++i) {
		_content[i].setnbseen(0);
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
	time_t		currenttime;
	bool		cont = true;
	int			lastid = 0;

	time(&currenttime);
	_deadborder = difftime(currenttime, _timer) / 20;
	_content[id].setnbseen(_content[id].getnbseen() + 1);
	if (_content[id].getnbseen() == 1)
		_player1.setnbcoins(_player1.getnbcoins() + 1);
	_display(id);
	usleep(SPEED);
	while (cont) {
		// try Right
		if (isinsidemaze(id) && fromdir != 1 && _idToX(id) < _sizex - 1 -_deadborder && !_content[_getidwithdir(id, 1)].getwallLeft()) {
			_depthFirstSearch(_getidwithdir(id, 1), 3);
			if (!isinsidemaze(id)) {
				lastid = id;
				break;
			}
			_content[id].setnbseen(_content[id].getnbseen() + 1);
			_display(id);
			usleep(SPEED);
		}
		// try Down
		if (isinsidemaze(id) && fromdir != 2 && _idToY(id) < _sizey - 1 - _deadborder && !_content[_getidwithdir(id, 2)].getwallUp()) {
			_depthFirstSearch(_getidwithdir(id, 2), 0);
			if (!isinsidemaze(id)) {
				lastid = id;
				break;
			}
			_content[id].setnbseen(_content[id].getnbseen() + 1);
			_display(id);
			usleep(SPEED);
		}
		// try Left
		if (isinsidemaze(id) && fromdir != 3 && _idToX(id) > _deadborder && !_content[id].getwallLeft()) {
			_depthFirstSearch(_getidwithdir(id, 3), 1);
			if (!isinsidemaze(id)) {
				lastid = id;
				break;
			}
			_content[id].setnbseen(_content[id].getnbseen() + 1);
			_display(id);
			usleep(SPEED);
		}
		// try Up
		if (isinsidemaze(id) && fromdir != 0 && _idToY(id) > _deadborder && !_content[id].getwallUp()) {
			_depthFirstSearch(_getidwithdir(id, 0), 2);
			if (!isinsidemaze(id)) {
				lastid = id;
				break;
			}
			_content[id].setnbseen(_content[id].getnbseen() + 1);
			_display(id);
			usleep(SPEED);
		}
		//_display(_getidwithdir(id, fromdir));
		_content[id].setnbseen(4);
		cont = false;
	}
	return (lastid);
}

int		Maze::isinsidemaze(int id) {
	if (_idToY(id) >= _deadborder && _idToX(id) <= _sizex - 1 -_deadborder && _idToY(id) <= _sizey - 1 - _deadborder && _idToX(id) >= _deadborder)
		return (1);
	else
		return (0);
}

int		Maze::_getidwithdir(int id, int dir) {
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

int		Maze::_finddirwithid(int from, int to) {
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

void 	Maze::_changegroupvalue(int oldvalue, int newvalue) {
	for (int i = 0; i < _sizex * _sizey; ++i) {
		if (this->_content[i].getvalue() == oldvalue) {
			this->_content[i].setvalue(newvalue);
		}
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
