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

bool Maze::getmode(void) {
	return (_mode);
}

void Maze::setmode(bool mode) {
	_mode = mode;
}

void	Maze::create(void) {
	int	k = _sizex * _sizey - 1;
	int	randcell;
	int	randdir;

	srand(time(0));
	while (k) {
//		std::cout << "********************************k = " << k << std::endl;
		Maze::_display(-1);
		randcell = rand() % (_sizex * _sizey);
		randdir = rand() % 2;
//		std::cout << "Random_cell : " << randcell << " (" << _idToX(randcell) << "x" << _idToY(randcell) << ")" << std::endl;
//			std::cout <<  "   Wall : " << randdir << std::endl;
//			std::cout <<  "   Value 1st cell " << this->_content[randcell].getvalue() << std::endl;
//			std::cout <<  "   Value LEFT cell " << this->_content[randcell - 1].getvalue() << std::endl;
//			std::cout <<  "   Value UP cell " << this->_content[randcell - _sizex].getvalue() << std::endl;
		if (randdir == 0 && _idToX(randcell) != 0 && _content[randcell].getvalue() != _content[randcell - 1].getvalue()) {
//			std::cout <<  "   Removing wallLeft" << std::endl;
			k--;
			this->_content[randcell].setnbseen(0);
//			std::cout <<  "   Value 1st cell " << this->_content[randcell].getvalue() << std::endl;
//			std::cout <<  "   Value LEFT cell " << this->_content[randcell - 1].getvalue() << std::endl;
//			std::cout <<  "   REMOVING WALL" << std::endl;
			this->_content[randcell].setwallLeft(false);
			Maze::_changegroupvalue(_max(this->_content[randcell - 1].getvalue(), this->_content[randcell].getvalue()), 
					_min(this->_content[randcell - 1].getvalue(), this->_content[randcell].getvalue()));
//			std::cout <<  "   Value 1st cell " << this->_content[randcell].getvalue() << std::endl;
//			std::cout <<  "   Value 2nd cell " << this->_content[randcell - 1].getvalue() << std::endl;
//			std::cout <<  "   Seen : " << this->_content[randcell].getseen() << std::endl;
//			std::cout <<  "   wallLeft : " << this->_content[randcell].getwallLeft() << std::endl;
//			std::cout <<  "   wallUp : " << this->_content[randcell].getwallUp() << std::endl;
//			std::cout <<  std::endl;
		}
		else if (randdir == 1 && _idToY(randcell) != 0 && _content[randcell].getvalue() != _content[randcell - _sizex].getvalue()) {
//			std::cout <<  "   Removing wallUp" << std::endl;
			k--;
			this->_content[randcell].setnbseen(0);
//			std::cout <<  "   Value 1st cell " << this->_content[randcell].getvalue() << std::endl;
//			std::cout <<  "   Value UP cell " << this->_content[randcell - _sizex].getvalue() << std::endl;
//			std::cout <<  "   REMOVING WALL" << std::endl;
			this->_content[randcell].setwallUp(false);
			Maze::_changegroupvalue(_max(this->_content[randcell - _sizex].getvalue(), this->_content[randcell].getvalue()), 
					_min(this->_content[randcell - _sizex].getvalue(), this->_content[randcell].getvalue()));
//			std::cout <<  "   Value 1st cell " << this->_content[randcell].getvalue() << std::endl;
//			std::cout <<  "   Value 2nd cell " << this->_content[randcell - _sizex].getvalue() << std::endl;
//			std::cout <<  "   Seen : " << this->_content[randcell].getseen() << std::endl;
//			std::cout <<  "   wallLeft : " << this->_content[randcell].getwallLeft() << std::endl;
//			std::cout <<  "   wallUp : " << this->_content[randcell].getwallUp() << std::endl;
//			std::cout <<  std::endl;
		}
	}
	Maze::_display(-1);
	setmode(1);
}

void	Maze::_display(int id) {
	std::string	colorgrid;
	std::string	colornumbers;

	if (_mode)
		colorgrid = GREEN;
	else
		colorgrid = MAGENTA;
	usleep(50000);
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	for (int j = 0; j < _sizey; ++j) {
		std::cout << std::setw(2) << " ";
		for (int i = 0; i < _sizex; ++i) {
			if (_content[i + j * _sizex].getwallUp()) {
				std::cout << colorgrid << std::setw(6) << "______" << RESET;
				std::cout << std::setw(2) << " ";
			}
			else {
				std::cout << std::setw(6) << " ";
				std::cout << std::setw(2) << " ";
			}
		}
		std::cout << std::endl;
		for (int i = 0; i < _sizex; ++i) {
			if (_content[i + j * _sizex].getwallLeft()) {
				std::cout << colorgrid << std::setw(2) << "|" << RESET;
			}
			else {
				std::cout << std::setw(2) << " ";
			}
			std::cout << std::setw(6) << " ";
		}
		std::cout << colorgrid << std::setw(2) << "|" << RESET;
		std::cout << std::endl;
		for (int i = 0; i < _sizex; ++i) {
			if (_mode)
				colornumbers = BOLDYELLOW;
			else
				colornumbers = Maze::_getcolor(_content[i + j * _sizex].getvalue());
			if (_content[i + j * _sizex].getwallLeft()) {
				std::cout << colorgrid << std::setw(2) << "|" << RESET;
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
					if (_content[i + j * _sizex].getvalue() == 0)
						std::cout << colornumbers << std::setw(3) << "o" << RESET;
					else
						std::cout << colornumbers << std::setw(3) << _content[i + j * _sizex].getvalue() << RESET;
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
		std::cout << colorgrid << std::setw(2) << "|" << RESET;
		std::cout << std::endl;
		for (int i = 0; i < _sizex; ++i) {
			if (_content[i + j * _sizex].getwallLeft()) {
				std::cout << colorgrid << std::setw(2) << "|" << RESET;
			}
			else {
				std::cout << std::setw(2) << " ";
			}
			std::cout << std::setw(6) << " ";
		}
		std::cout << colorgrid << std::setw(2) << "|" << RESET;
		std::cout << std::endl;
	}
	std::cout << std::setw(2) << " ";
	for (int i = 0; i < _sizex; ++i) {
		std::cout << colorgrid << std::setw(6) << "______" << RESET;
		std::cout << std::setw(2) << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

void	Maze::explore(void) {
	_findNextCell(0, -1);
}

int	Maze::_findNextCell(int id, int fromdir) {
	//std::cout << "Current cell : " << id << std::endl;
	//std::cout << "from dir : " << fromdir << std::endl;
	//std::cout << "reverse : " << reverse << std::endl;
	_content[id].setnbseen(_content[id].getnbseen() + 1);
	_display(id);
	usleep(100000);
		// try Up
		if (fromdir != 0 && !_content[id].getwallUp()) {
			_findNextCell(_getidwithdir(id, 0), 2);
			_content[id].setnbseen(_content[id].getnbseen() + 1);
			_display(id);
			usleep(100000);
		}
		// try Right
		if (fromdir != 1 && _idToX(id) < _sizex - 1 && !_content[_getidwithdir(id, 1)].getwallLeft()) {
			_findNextCell(_getidwithdir(id, 1), 3);
			_content[id].setnbseen(_content[id].getnbseen() + 1);
			_display(id);
			usleep(100000);
		}
		// try Down
		if (fromdir != 2 && _idToY(id) < _sizey - 1 && !_content[_getidwithdir(id, 2)].getwallUp()) {
			_findNextCell(_getidwithdir(id, 2), 0);
			_content[id].setnbseen(_content[id].getnbseen() + 1);
			_display(id);
			usleep(100000);
		}
		// try Left
		if (fromdir != 3 && !_content[id].getwallLeft()) {
			_findNextCell(_getidwithdir(id, 3), 1);
			_content[id].setnbseen(_content[id].getnbseen() + 1);
			_display(id);
			usleep(100000);
		}
		//_display(_getidwithdir(id, fromdir));
	_content[id].setnbseen(4);
	return (-1);
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
