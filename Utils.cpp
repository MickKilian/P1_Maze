#include "Utils.hpp"

std::string	Utils::getColor(int nb) {
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

double	Utils::min(double a, double b) {
	if (a < b)
		return (a);
	else
		return (b);
}

double Utils::max(double a, double b) {
	if (a > b)
		return (a);
	else
		return (b);
}

double	Utils::cellIdToX(int id, int sizex) {
	return (id % sizex);
}

double	Utils::cellIdToY(int id, int sizex) {
	return (id / sizex);
}

int	Utils::xyToCellId(double x, double y, int sizex) {
	if (x == -0.5)
		x = 0;
	if (y == -0.5)
		y = 0;
	return (round(x) + round(y) * sizex);
}

int	Utils::getIdWithDir(int id, int dir, int sizex) {
	// find id on adjacent node depending on direction:
	// 0. up
	// 1. right
	// 2. down
	// 3. left
	switch (dir) {
		case 0:
			return (id - sizex);
			break;
		case 1:
			return (id + 1);
			break;
		case 2:
			return (id + sizex);
			break;
		case 3:
			return (id - 1);
			break;
		default:
			return (-1);
	}
}

int	Utils::findDirWithId(int from, int to, int sizex) {
	if (to == from - sizex)
		return (0);
	else if (to == from + 1)
		return (1);
	else if (to == from + sizex)
		return (2);
	else if (to == from - 1)
		return (3);
	else
		return (-1);
}

void	Utils::printInColor(int width, std::string text, std::string textColor, std::string backColor) {
	std::cout << textColor << backColor << std::setw(width) << text << RESET;
}
