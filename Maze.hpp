#ifndef MAZE_H
#define MAZE_H

#include "Cell.hpp"
#include "Player.hpp"
#include <vector>
#include <string>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <unistd.h>
#include <time.h>		/* time_t, struct tm, difftime, time, mktime */

#define RED				"\x1b[31m"
#define BOLDRED			"\x1b[31;1m"
#define GREEN			"\x1b[32m"
#define BOLDGREEN		"\x1b[32;1m"
#define YELLOW			"\x1b[33m"
#define BOLDYELLOW		"\x1b[33;1m"
#define BLUE			"\x1b[34m"
#define MAGENTA			"\x1b[35m"
#define BOLDMAGENTA		"\x1b[35;1m"
#define CYAN			"\x1b[36m"
#define BOLDCYAN		"\x1b[36;1m"
#define WHITE			"\x1b[37m"
#define RESET			"\x1b[0m"

#define SPEED			500000
#define MAKE			10000

class	Maze {
	public:
		Maze();
		Maze(int, int);
		~Maze(void);
		bool	getmode(void);
		void	setmode(bool mode);
		void	settimer(time_t);
		void	create(void);
		void	explore(void);
		int		isinsidemaze(int);

	private:
		int					_sizex;
		int					_sizey;
		std::vector<Cell>	_content;
		Player				_player1;
		bool				_mode;
		time_t				_timer;
		int					_deadborder;
		void 				_display(int id);
		int					_idToX(int id);
		int					_idToY(int id);
		void				_changegroupvalue(int oldvalue, int newvalue);
		int					_getidwithdir(int id, int dir);
		int					_finddirwithid(int from, int to);
		int					_findNextCell(int id, int fromdir);
		static std::string	_getcolor(int nb);
		static int			_min(int, int);
		static int			_max(int, int);
};

Maze*	newMaze(int, int);

#endif // MAZE_H
