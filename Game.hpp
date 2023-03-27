#ifndef GAME_H
#define GAME_H

#include "Maze.hpp"
#include "Utils.hpp"
#include "Player.hpp"
#include <time.h>		/* time_t, struct tm, difftime, time, mktime */

#define	SIZE_X			10	//maze size in x-direction
#define	SIZE_Y			10	//maze size in y-direction
#define	NB_PLAYERS		1
#define	TOTAL_GAME_TIME	120 // total game time (in sec)
#define	SHRINKING_SPEED	5 //time (in sec) it takes to shrink one row of the maze
#define	INITIAL_CELL		0		//initial cell position of all players
#define	INITIAL_ORIENTATION	180		//initial orientation 180deg: DOWN
#define	MAX_SPEED			1000	//Maximum moving speed of players

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
		void		display();

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
