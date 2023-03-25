#ifndef PATH_H
#define PATH_H

#include <vector>
#include "Cell.hpp"

class	Path {
	public:
		Path();
		Path(int, int);
		~Path(void);
		int			getLength(void);
		int			getcurCell(void);
		void		setLength(int length);
		void		setcurCell(int cell);

	private:

		std::vector<Cell>		_cells;
		int						_length;
		int						_curCell;
};

#endif // PATH_H
