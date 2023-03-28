#ifndef PATH_H
#define PATH_H

#include "Point.hpp"
#include <vector>
#include <iostream>

class	Path {
	public:
		Path();
		Path(Point);
		~Path(void);
		std::vector<Point>	getPoint();
		void				addPoint(Point);
		void				display();

	private:
		std::vector<Point>	_point;
};

#endif // PATH_H
