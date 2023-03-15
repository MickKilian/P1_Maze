#include "Maze.hpp"

int	main() {
	Maze*	maze = newMaze(15, 15);
	time_t	startingtime;

	time(&startingtime);
	maze->settimer(startingtime);
	maze->create();
	time(&startingtime);
	maze->settimer(startingtime);
	maze->explore();
	delete maze;
	return 0;
}
