#include "Game.hpp"

int	main() {
	Game*	game = new Game();

	game->setMaze(game->getMaze().create());
	game->display();

	game->setMode(1);
	game->explore();
	//game->display();
	delete game;
	return 0;
}
