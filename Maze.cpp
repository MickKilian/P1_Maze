#include "Maze.hpp"

Maze::Maze() {
}

Maze::Maze(int sizex, int sizey) : _sizex(sizex), _sizey(sizey) {
	//std::cout << "A maze of size : " << _sizex << "x" << _sizey << " is being born" << std::endl;
	for (int i = 0; i < sizex * sizey; ++i) {
		_content.push_back(Cell(i , i, false, true, true));
//		_content[i].display();
	}
}

Maze::~Maze() {
	//std::cout << "A maze of size : " << _sizex << "x" << _sizey << " is deleted" << std::endl;
}

void	Maze::create(void) {
	int	k = _sizex * _sizey - 1;
	int	randcell;
	int	randdir;

	srand(time(0));
	while (k) {
//		std::cout << "********************************k = " << k << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		std::cout << std::endl;
		Maze::display();
		usleep(50000);
		randcell = rand() % (_sizex * _sizey);
		randdir = rand() % 2;
//		std::cout << "Random_cell : " << randcell << " (" << idToX(randcell) << "x" << idToY(randcell) << ")" << std::endl;
//			std::cout <<  "   Wall : " << randdir << std::endl;
//			std::cout <<  "   Value 1st cell " << this->_content[randcell].getvalue() << std::endl;
//			std::cout <<  "   Value LEFT cell " << this->_content[randcell - 1].getvalue() << std::endl;
//			std::cout <<  "   Value UP cell " << this->_content[randcell - _sizex].getvalue() << std::endl;
		if (randdir == 0 && idToX(randcell) != 0 && _content[randcell].getvalue() != _content[randcell - 1].getvalue()) {
//			std::cout <<  "   Removing wallLeft" << std::endl;
			k--;
			this->_content[randcell].setseen(true);
//			std::cout <<  "   Value 1st cell " << this->_content[randcell].getvalue() << std::endl;
//			std::cout <<  "   Value LEFT cell " << this->_content[randcell - 1].getvalue() << std::endl;
//			std::cout <<  "   REMOVING WALL" << std::endl;
			this->_content[randcell].setwallLeft(false);
			Maze::changegroupvalue(this->_content[randcell - 1].getvalue(), this->_content[randcell].getvalue());
//			std::cout <<  "   Value 1st cell " << this->_content[randcell].getvalue() << std::endl;
//			std::cout <<  "   Value 2nd cell " << this->_content[randcell - 1].getvalue() << std::endl;
//			std::cout <<  "   Seen : " << this->_content[randcell].getseen() << std::endl;
//			std::cout <<  "   wallLeft : " << this->_content[randcell].getwallLeft() << std::endl;
//			std::cout <<  "   wallUp : " << this->_content[randcell].getwallUp() << std::endl;
//			std::cout <<  std::endl;
		}
		else if (randdir == 1 && idToY(randcell) != 0 && _content[randcell].getvalue() != _content[randcell - _sizex].getvalue()) {
//			std::cout <<  "   Removing wallUp" << std::endl;
			k--;
			this->_content[randcell].setseen(true);
//			std::cout <<  "   Value 1st cell " << this->_content[randcell].getvalue() << std::endl;
//			std::cout <<  "   Value UP cell " << this->_content[randcell - _sizex].getvalue() << std::endl;
//			std::cout <<  "   REMOVING WALL" << std::endl;
			this->_content[randcell].setwallUp(false);
			Maze::changegroupvalue(this->_content[randcell - _sizex].getvalue(), this->_content[randcell].getvalue());
//			std::cout <<  "   Value 1st cell " << this->_content[randcell].getvalue() << std::endl;
//			std::cout <<  "   Value 2nd cell " << this->_content[randcell - _sizex].getvalue() << std::endl;
//			std::cout <<  "   Seen : " << this->_content[randcell].getseen() << std::endl;
//			std::cout <<  "   wallLeft : " << this->_content[randcell].getwallLeft() << std::endl;
//			std::cout <<  "   wallUp : " << this->_content[randcell].getwallUp() << std::endl;
//			std::cout <<  std::endl;
		}
	}
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	Maze::display();
}

void	Maze::display(void) {
	for (int j = 0; j < _sizey; ++j) {
		std::cout << std::setw(2) << " ";
		for (int i = 0; i < _sizex; ++i) {
			if (_content[i + j * _sizex].getwallUp()) {
				std::cout << GREEN << std::setw(6) << "______" << RESET;
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
				std::cout << GREEN << std::setw(2) << "|" << RESET;
			}
			else {
				std::cout << std::setw(2) << " ";
			}
			std::cout << std::setw(6) << " ";
		}
		std::cout << GREEN << std::setw(2) << "|" << RESET;
		std::cout << std::endl;
		for (int i = 0; i < _sizex; ++i) {
			if (_content[i + j * _sizex].getwallLeft()) {
				std::cout << GREEN << std::setw(2) << "|" << RESET;
			}
			else {
				std::cout << std::setw(2) << " ";
			}
			std::cout << MAGENTA << std::setw(6) << _content[i + j * _sizex].getvalue() << RESET;
			//std::cout << MAGENTA << std::setw(6) << "   o  " << RESET;
		}
		std::cout << GREEN << std::setw(2) << "|" << RESET;
		std::cout << std::endl;
		for (int i = 0; i < _sizex; ++i) {
			if (_content[i + j * _sizex].getwallLeft()) {
				std::cout << GREEN << std::setw(2) << "|" << RESET;
			}
			else {
				std::cout << std::setw(2) << " ";
			}
			std::cout << std::setw(6) << " ";
		}
		std::cout << GREEN << std::setw(2) << "|" << RESET;
		std::cout << std::endl;
	}
	std::cout << std::setw(2) << " ";
	for (int i = 0; i < _sizex; ++i) {
		std::cout << GREEN << std::setw(6) << "______" << RESET;
		std::cout << std::setw(2) << " ";
	}
	std::cout << std::endl;
}

void	Maze::explore(void) {
	findNextCell(0, -1, false);
}

int		Maze::findNextCell(int id, int fromdir, bool reverse) {
	std::cout << "Current cell : " << id << std::endl;
	std::cout << "from dir : " << fromdir << std::endl;
	std::cout << "reverse : " << reverse << std::endl;
	usleep(200000);
	if (!reverse) {
		// try Up
		if (fromdir != 0 && !_content[id].getwallUp())
			return (findNextCell(getidwithdir(id, 0), 2, false));
		// try Right
		else if (fromdir != 1 && idToX(id) < _sizex && !_content[getidwithdir(id, 1)].getwallLeft())
			return (findNextCell(getidwithdir(id, 1), 3, false));
		// try Down
		else if (fromdir != 2 && idToY(id) < _sizey && !_content[getidwithdir(id, 2)].getwallUp())
			return (findNextCell(getidwithdir(id, 2), 0, false));
		// try Left
		else if (fromdir != 3 && !_content[id].getwallLeft())
			return (findNextCell(getidwithdir(id, 3), 1, false));
		else
			return (findNextCell(getidwithdir(id, fromdir), (fromdir + 2) % 4, true));
	}
	else {
	}
	return (-1);
}

int		Maze::getidwithdir(int id, int dir) {
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

int		Maze::finddirwithid(int from, int to) {
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

int		Maze::idToX(int id) {
	return (id % _sizex);
}

int		Maze::idToY(int id) {
	return (id / _sizex);
}

void 	Maze::changegroupvalue(int oldvalue, int newvalue) {
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
