#include "Route.hpp"

Route::Route() : _cell() {
}

Route::Route(int value) {
	_cell.push_back(value);
}

Route::~Route() {
}

std::vector<int>	Route::getCell() {
	return (_cell);
}

void	Route::setCurCell(int cellId) {
	_curCell = cellId;
}

void	Route::addCell(int value) {
	_cell.push_back(value);
}

void	Route::display() {
	std::cout << "Displaying route!" << std::endl;
	std::cout << "Nb elements : " << _cell.size() << std::endl;
	for (int i = 0; i < static_cast<int>(_cell.size()); ++i) {
		std::cout << _cell[i] << std::endl;
	}
}
