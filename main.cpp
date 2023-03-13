#include "Maze.hpp"

int	main() {
	Maze*	maze = newMaze(10, 10);

	maze->create();
	maze->explore();
	delete maze;
	return 0;
}
