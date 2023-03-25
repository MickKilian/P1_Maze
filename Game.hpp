#ifndef GAME_H
#define GAME_H

#include <time.h>		/* time_t, struct tm, difftime, time, mktime */
#include "Path.hpp"

class	Game {
	public:
		Game();
		Game(int, time_t, int);
		~Game(void);
		int			getNbPlayers(void);
		time_t		getCurTime(void);
		int			getRemainingCoins(void);
		void		getNbPlayers(int);
		void		getCurTime(time_t);
		void		getRemainingCoins(int);

	private:
		int			_nbPlayers;
		time_t		_curTime;
		int			_remainingCoins;
};

#endif // GAME_H
