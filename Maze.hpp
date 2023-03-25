#ifndef MAZE_H
#define MAZE_H

#include "Cell.hpp"
#include "Dijkstra.hpp"
#include "Player.hpp"
#include "Path.hpp"
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <time.h>		/* time_t, struct tm, difftime, time, mktime */

#define	RED				"\x1b[31m"
#define	BOLDRED			"\x1b[31;1m"
#define	GREEN			"\x1b[32m"
#define	BOLDGREEN		"\x1b[32;1m"
#define	YELLOW			"\x1b[33m"
#define	BOLDYELLOW		"\x1b[33;1m"
#define	BLUE			"\x1b[34m"
#define	MAGENTA			"\x1b[35m"
#define	BOLDMAGENTA		"\x1b[35;1m"
#define	CYAN			"\x1b[36m"
#define	BOLDCYAN		"\x1b[36;1m"
#define	WHITE			"\x1b[37m"
#define	RESET			"\x1b[0m"

#define	SPEED			250000
#define	MAKE			0000
#define	SHRINK_TIME		10
#define	SOLVING_ALGO	2 // 0: DFS, 1: DIJKSTRA, 2: GET ALL SIDES with DIJKSTRA

class	Maze {
	public:
		Maze();
		Maze(int, int);
		~Maze();
		bool	getmode();
		void	setmode(bool);
		void	settimer(time_t);
		void	create();
		void	explore();
		int		isInAllowedMaze(int);
		void	displayDijkstraTable();
		void	readDijkstraPath(int, int);
		int		countDijkstraPath(int, int);
		void	resetPath();
		void	resetDijkstraTable();
		int		updateStatus();
		int		borderDijkstra(int, bool);

	private:
		int						_sizex;
		int						_sizey;
		std::vector<Cell>		_cell;
		Player					_player1;
		bool					_mode;				//0: creation mode, 1: exploration mode
		time_t					_timer;
		double					_borderPosition;	//in a maze shrinking mode, this parameter is the forbidden distance (in cell size unit) from maze edge
		int						_deadborder;		//in a maze shrinking mode, this parameter is the forbidden distance (in cell size unit) from maze edge
		std::vector<Dijkstra>	_dijkstraTable;		//is the Dijkstra table for path search using Dijkstra algorithm
		void 					_display(int id);
		int						_idToX(int id);
		int						_idToY(int id);
		int						_XYToId(int x, int y);
		void					_fillWalls();
		void					_changeGroupValue(int oldvalue, int newvalue);
		int						_getIdWithDir(int id, int dir);
		int						_finDirWithId(int from, int to);
		int						_depthFirstSearch(int id, int fromdir);
		int						_dijkstra(int, int, int = -1);
		void					_addToDijkstraTable(int curNode, int adjNode);
		int						_findNextNodeToDijkstraVisit();
		static std::string		_getcolor(int nb);
		static int				_min(int, int);
		static int				_max(int, int);
};

Maze*	newMaze(int, int);

#endif // MAZE_H
