#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Path.hpp"

class	Player {
	public:
		Player();
		Player(std::string, int, int, int, int, int, int, int);
		~Player(void);
		std::string	getName(void);
		double		getX(void);
		double		getY(void);
		int			getId(void);
		int			getCell(void);
		int			getNbCoins(void);
		int			getLives(void);
		int			getMode(void);
		int			getSpeed(void);
		int			getStrategy(void);
		void		setName(std::string);
		void		setX(double x);
		void		setY(double y);
		void		setId(int);
		void		setCell(int);
		void		setNbCoins(int);
		void		setLives(int);
		void		setMode(int);
		void		setSpeed(int);
		void		setStrategy(int);

	private:
		std::string	_name;
		double		_x;
		double		_y;
		int			_id;
		int			_cell;
		int			_nbcoins;
		int			_lives;
		int			_mode;
		int			_speed;
		int			_strategy;
		Path		_path;
};

#endif // PLAYER_H
