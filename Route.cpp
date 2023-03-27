#include "Route.hpp"

Route::Route() : _cell() {
	std::cout << "A route was constructed" << std::endl;
}

Route::~Route() {
}

std::vector<int>	Route::getCell() {
	return (_cell);
}

void	Route::setCurCell(int cellId) {
	_curCell = cellId;
}

void	Route::display() {
	std::cout << "Displaying route!" << std::endl;
	for (int i = 0; i < static_cast<int>(_cell.size()); ++i) {
		std::cout << _cell[i] << std::endl;
	}
}
