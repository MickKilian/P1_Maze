#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class	Player {
	public:
		Player();
		Player(std::string, int, int, int, int, int, int, int);
		~Player(void);
		std::string	getname(void);
		int			getid(void);
		int			getcell(void);
		int			getnbcoins(void);
		int			getlives(void);
		int			getmode(void);
		int			getspeed(void);
		int			getstrategy(void);
		void		setname(std::string);
		void		setid(int);
		void		setcell(int);
		void		setnbcoins(int);
		void		setlives(int);
		void		setmode(int);
		void		setspeed(int);
		void		setstrategy(int);
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
