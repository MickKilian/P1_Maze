#ifndef PATH_H
#define PATH_H

#include "Step.hpp"
#include <vector>

class	Path {
	public:
		Path();
		~Path(void);

	private:
		std::vector<Step>	_step;
};

#endif // PATH_H
