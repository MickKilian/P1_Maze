#ifndef CELL_H
#define CELL_H

#include <string>

class	Cell {
	public:
		Cell();
		Cell(int, int, int, int, bool, bool, bool, bool);
		~Cell();
		int		getValue();
		int		getNbSeen();
		int		getStatus();
		bool	getWall(int dir);
		void	setValue(int value);
		void	setNbSeen(int nb);
		void	setStatus(int status);
		void	setWall(int dir, bool wall);
		void	display();

	private:
		int		_id;
		int		_value;
		int		_nbseen;
		int		_status;
		bool	_wall[4];
};

#endif // CELL_H
