#include "Path.hpp"

Path::Path() : _length(-1), _curCell(-1) {
}

Path::Path(int length, int curCell) : _length(length), _curCell(curCell) {
}

Path::~Path() {
}

int			Path::getLength() {
	return (_length);
}

int			Path::getcurCell() {
	return (_curCell);
}

void		Path::setLength(int length) {
	_length = length;
}

void		Path::setcurCell(int cell) {
	_curCell = cell;
}
