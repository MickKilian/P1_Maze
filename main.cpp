#include "Maze.hpp"

int	main() {
	Maze*	maze = newMaze(12, 12);

	maze->create();
	maze->explore();
	delete maze;
	return 0;
}
