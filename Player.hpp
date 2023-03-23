#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class	Player {
	public:
		Player();
		Player(std::string, int, int, int, int, int, int, int);
		~Player(void);
		std::string	getName(void);
		int			getId(void);
		int			getCell(void);
		int			getNbCoins(void);
		int			getLives(void);
		int			getMode(void);
		int			getSpeed(void);
		int			getStrategy(void);
		void		setName(std::string);
		void		setId(int);
		void		setCell(int);
		void		setNbCoins(int);
		void		setLives(int);
		void		setMode(int);
		void		setSpeed(int);
		void		setStrategy(int);
		void		display();

	private:
		std::string	_name;
		int			_id;
		int			_cell;
		int			_nbcoins;
		int			_lives;
		int			_mode;
		int			_speed;
		int			_strategy;
};

#endif // PLAYER_H
