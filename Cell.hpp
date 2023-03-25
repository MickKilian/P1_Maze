#ifndef CELL_H
#define CELL_H

#include <string>

class	Cell {
	public:
		Cell();
		Cell(int, int, int, int, bool, bool, bool, bool);
		~Cell();
		int		getId();
		int		getValue();
		int		getNbSeen();
		int		getStatus();
		bool	getWall(int);
		void	setId(int);
		void	setValue(int);
		void	setNbSeen(int);
		void	setStatus(int);
		void	setWall(int, bool);

	private:
		int		_id;		//id of the cell in maze
		int		_value;		//used during maze creation. Initially, all cells have id for value, and then cells are "grouped" sharing their value until only value "0" remains
		int		_nbseen;	//nb of times that the cell was seen
		int		_status;	//0: cell is outside of allowed zone, 1: cell is inside of allowed zone
		bool	_wall[4];	//existence of each wall 0: UP, 1: RIGHT, 2, DOWN, 3: LEFT
};

#endif // CELL_H
