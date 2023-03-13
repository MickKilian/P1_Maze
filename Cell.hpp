#ifndef CELL_H
#define CELL_H

#include <string>

class	Cell {
	public:
		Cell();
		Cell(int, int, bool, bool, bool);
		~Cell(void);
		int		getvalue();
		bool	getseen();
		bool	getwallLeft();
		bool	getwallUp();
		void	setvalue(int value);
		void	setseen(bool seen);
		void	setwallLeft(bool wall);
		void	setwallUp(bool wall);
		void	display();

	private:
		int		_id;
		int		_value;
		bool	_seen;
		bool	_wallLeft;
		bool	_wallUp;
};

#endif // CELL_H
