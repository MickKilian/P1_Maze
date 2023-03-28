#ifndef GAME_H
#define GAME_H

#include "Maze.hpp"
#include "Utils.hpp"
#include "Player.hpp"
#include <cstdlib>		//rand
#include <time.h>		/* time_t, struct tm, difftime, time, mktime */

#define	SIZE_X				12		//maze size in x-direction
#define	SIZE_Y				12		//maze size in y-direction
#define	TIME_STEPINC		1000000	//time (in us) inc for player's steps computation
#define	DIM_STEPINC			0.1		//distance (in mm) inc for player's steps on its path
#define	NB_PLAYERS			3
#define	TOTAL_GAME_TIME		120		//total game time (in sec)
#define	SHRINKING_SPEED		500		//time (in sec) it takes to shrink one row of the maze
#define	INITIAL_CELL		0		//initial cell position of all players
#define	INITIAL_ORIENTATION	90		//initial orientation 180deg: DOWN
#define	MAX_SPEED			100000	//Maximum moving speed of players
#define	FORCE_FORWARD		1		//0: can go backwards, 1: can only go forward
#define	TOLERANCE			0.01	//dist (in mm) under which two points are considered the same

class	Game {
	public:
		Game();
		~Game(void);
		Maze		getMaze(void);
		int			getMode();
		int			getNbPlayers(void);
		time_t		getStartingTime(void);
//		time_t		getCurTime(void);
		time_t		getTotalGameTime(void);
		int			getShrinkingSpeed(void);
		int			getRemainingCoins(void);
		void		setMaze(Maze);
		void		setMode(int);
		void		setNbPlayers(int);
		void		setStartingTime(time_t);
//		void		setCurTime(time_t);
		void		setTotalGameTime(time_t);
		void		setShrinkingSpeed(int);
		void		setRemainingCoins(int);
//		int			updateStatus();
		void		updateAll();
		void		updateBorder();
		bool		isInDeadZone(double, double);
//		int			isInAllowedMaze(int);
		void		explore();
		void		startNewRoute(int);
		void		display();
		bool		playerIsOnSpot(int, double, double);
		std::string	getDirIcon(int);

	private:
		Maze				_maze;
		int					_mode;				//0: maze creation mode, 1: maze exploration mode
		int					_nbPlayers;
		std::vector<Player>	_player;
		time_t				_startingTime;
//		time_t				_curTime;
		time_t				_totalGameTime;
		double				_borderPosition;	//in a maze shrinking mode, this parameter is the forbidden distance (in cell size unit) from maze edge
		int					_shrinkingSpeed;
		int					_remainingCoins;
};

#endif // GAME_H
