#include "Path.hpp"

Path::Path() {
}

Path::Path(Point point) {
	_point.push_back(point);
}

Path::~Path() {
}

std::vector<Point>	Path::getPoint() {
	return (_point);
}

void	Path::addPoint(Point point) {
	_point.push_back(point);
}

void	Path::display() {
	std::cout << "Displaying path!" << std::endl;
	std::cout << "Nb elements : " << _point.size() << std::endl;
	for (unsigned i = 0; i < _point.size(); ++i) {
		std::cout << i << " : (" << _point[i].getX() << ", " << _point[i].getY() << ")" << std::endl;
	}
}
