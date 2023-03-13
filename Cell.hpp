#ifndef CELL_H
#define CELL_H

#include <string>

class	Cell {
	public:
		Cell();
		Cell(int, int, int, bool, bool);
		~Cell(void);
		int		getvalue();
		int		getnbseen();
		bool	getwallLeft();
		bool	getwallUp();
		void	setvalue(int value);
		void	setnbseen(int nb);
		void	setwallLeft(bool wall);
		void	setwallUp(bool wall);
		void	display();

	private:
		int		_id;
		int		_value;
		int		_nbseen;
		bool	_wallLeft;
		bool	_wallUp;
};

#endif // CELL_H
