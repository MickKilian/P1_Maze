#include "Maze.hpp"

Maze::Maze() {
}

Maze::Maze(int sizex, int sizey) : _sizex(sizex), _sizey(sizey) {
	//std::cout << "A maze of size : " << _sizex << "x" << _sizey << " is being born" << std::endl;
	_mode = 0;
	for (int i = 0; i < sizex * sizey; ++i) {
		_content.push_back(Cell(i , i, false, true, true));
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
		Maze::_display(-1);
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
					std::cout << RED << std::setw(3) << "." << RESET;
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
		if (j == 0)
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

	retid = 0;
	while (1) {
		std::cout << "retid : " << retid << std::endl;
		retid = _findNextCell(retid, -1);
	}

	std::cout << "Congratulations, player1 has collected " << _player1.getnbcoins() << " coins." << std::endl;
}

int	Maze::_findNextCell(int id, int fromdir) {
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
			_findNextCell(_getidwithdir(id, 1), 3);
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
			_findNextCell(_getidwithdir(id, 2), 0);
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
			_findNextCell(_getidwithdir(id, 3), 1);
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
			_findNextCell(_getidwithdir(id, 0), 2);
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
