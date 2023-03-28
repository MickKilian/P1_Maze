#ifndef ROUTE_H
#define ROUTE_H

#include <vector>
#include <iostream>

class	Route {
	public:
		Route();
		Route(int);
		~Route();
		std::vector<int>	getCell();
		void				setCurCell(int);
		void				addCell(int);
		void				display();

	private:
		int					_curCell;	//index of current cell in Route
		std::vector<int>	_cell;		//vector of all cells id composing projected route
};

#endif // ROUTE_H
