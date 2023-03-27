#ifndef MAZE_H
#define MAZE_H

#include "Route.hpp"
#include "Utils.hpp"
#include "Cell.hpp"
#include "Dijkstra.hpp"
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
#include <unistd.h>
#include <time.h>		//time_t, struct tm, difftime, time, mktime

#define	MAKE_SPEED		0			//SPEED (in us) to visualize make making
#define	SPEED			1000000		//SPEED (in us) of player

class	Maze {
	public:
		Maze();
		Maze(int, int);
		~Maze();
		int					getSizeX();
		int					getSizeY();
		std::vector<Cell>	getCell();
		Maze				create();
		int					borderDijkstra(int, bool);
		void				displayDijkstraTable();
		int					countDijkstraPath(int, int);
		void				resetDijkstraTable();
		Route				readDijkstraPath(int, int, Route);
		int					dijkstra(int, int, int = -1);
		void				addToDijkstraTable(int, int);
		int					findNextNodeToDijkstraVisit();
//		int					depthFirstSearch(int, int = 0);

	private:
		int						_sizex;				//dimension of maze in x_direction
		int						_sizey;				//dimension of maze in y_direction
//		int						_curStrategy;		//0: DFS, 1: DIJKSTRA, 2: GET ALL SIDES with DIJKSTRA
		std::vector<Dijkstra>	_dijkstraTable;		//is the Dijkstra table for path search using Dijkstra algorithm
		std::vector<Cell>		_cell;
		int						_nbCollectedCoins;	//for current player
		void					_fillWalls();
		void					_changeGroupValue(int oldvalue, int newvalue);
};

#endif // MAZE_H
