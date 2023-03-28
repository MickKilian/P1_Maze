/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 03:03:58 by mbourgeo          #+#    #+#             */
/*   Updated: 2023/03/28 12:39:45 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"

Game::Game() : _mode(0), _nbPlayers(NB_PLAYERS), _totalGameTime(TOTAL_GAME_TIME),
	_shrinkingSpeed(SHRINKING_SPEED), _remainingCoins(SIZE_X * SIZE_Y) {
	_maze = Maze(SIZE_X, SIZE_Y);
	for (int i = 0; i < _nbPlayers; ++i) {
		_player.push_back(Player(i, 0, Point(Utils::cellIdToX(INITIAL_CELL, SIZE_X),
			Utils::cellIdToY(INITIAL_CELL, SIZE_X)), INITIAL_ORIENTATION, 0, 1, 1,
			MAX_SPEED, PLAYER_STRATEGY, INITIAL_CELL, SIZE_X, SIZE_Y, DIM_STEPINC,
			FORCE_FORWARD, TOLERANCE, false, 0));
	}
	time(&_startingTime);
}

Game::~Game() {
}

Maze	Game::getMaze(void) {
	return (_maze);
}

int	Game::getMode(void) {
	return (_mode);
}

int	Game::getNbPlayers(void) {
	return (_nbPlayers);
}

time_t	Game::getStartingTime(void) {
	return(_startingTime);
}

/*time_t		Game::getCurTime(void) {
	return(_curTime);
}*/

time_t	Game::getTotalGameTime(void) {
	return(_totalGameTime);
}

int	Game::getShrinkingSpeed(void) {
	return (_shrinkingSpeed);
}

int	Game::getRemainingCoins(void) {
	return (_remainingCoins);
}

void	Game::setMaze(Maze maze) {
	_maze = maze;
}

void	Game::setMode(int mode) {
	_mode = mode;
}

void	Game::setNbPlayers(int nbPlayers) {
	_nbPlayers = nbPlayers;
}

/*void		Game::setCurTime(time_t time) {
	_curTime = time;
}*/

void	Game::setStartingTime(time_t time) {
	_startingTime = time;
}

void	Game::setTotalGameTime(time_t time) {
	_totalGameTime = time;
}

void	Game::setShrinkingSpeed(int speed) {
	_shrinkingSpeed = speed;
}

void	Game::setRemainingCoins(int coins) {
	_remainingCoins = coins;
}

/*int		Game::updateStatus() {
	for (int id = 0; id < _maze.getSizeX() * _maze.getSizeY(); ++id) {
		if (Utils::cellIdToX(id) + 1 < _maze.getBorderPosition() || _maze.getSizeX() - Utils::cellIdToX(id) < _maze.getBorderPosition() || Utils::cellIdToY(id) + 1 < _maze.getBorderPosition() || _maze.getSizeY() - Utils::cellIdToY(id) < _maze.getBorderPosition())
			this->_maze.getCell()[id].setStatus(0);
		else
			this->_maze.getCell()[id].setStatus(1);
	}
	return (0);
}*/

void	Game::updateAll() {
	updateBorder();
}

void	Game::updateBorder() {
	time_t	currentTime;

	time(&currentTime);
	_borderPosition = difftime(currentTime, _startingTime) / _shrinkingSpeed;
};

bool	Game::isInDeadZone(double x, double y) {
	return (x < (_borderPosition - 0.5) || y < (_borderPosition - 0.5)
			|| x > SIZE_X - 1 -(_borderPosition - 0.5) || y > SIZE_Y - 1 - (_borderPosition - 0.5));
}

/*int		Game::isInAllowedMaze(int id) {

	updateStatus();
	if (_maze.getCell()[id].getStatus())
		return (1);
	else
		return (0);
}*/

void	Game::explore(void) {
	srand(time(0));
	for (int id = 0; id < _nbPlayers; ++id) {
		_player[id].setStartingCell(rand() % (SIZE_X * SIZE_Y));
		//std::cout << "check : " << _player[id].getStartingCell() << std::endl;
		startNewRoute(id);
	}
	while (_player[0].getMoving() || _player[1].getMoving() || _player[2].getMoving()) {
		for (int id = 0; id < 3; ++id) {
			usleep(MAX_SPEED / 3);
			if (_player[id].getMoving()) {
				_player[id].move();
				display();
			}
			else
			{
				//std::cout << "check : ";
				_player[id].getPosition().display();
				//std::cout << std::endl;
				_player[id].setStartingCell(Utils::pointToCellId(_player[id].getPosition(), SIZE_X));
				//std::cout << "check : " << _player[id].getStartingCell() << std::endl;
				//_player[id].setRoute(Route());
				_player[id].setIndexInPath(0);
				//usleep(1000000);
				startNewRoute(id);
			}
		}
	}
	//_player[0].getAction().decision(Point(1, 1));
	//_player[0].getMovement().describe("Michael");
}

void	Game::startNewRoute(int playerId) {
	_player[playerId].setPosition(Utils::cellIdToPoint(_player[playerId].getStartingCell(), SIZE_X));
	//std::cout << "check : " << _player[playerId].getStartingCell() << std::endl;
	//usleep(1000000);
	_player[playerId].setRoute(_maze.findRoute(_player[playerId].getStartingCell(), rand() % (SIZE_X * SIZE_Y)));
	//_player[0].getRoute().display();
	_player[playerId].setPath(_player[playerId].calcPath(_player[playerId].getRoute(), 0));
	//_player[0].getPath().display();
	//_player[0].printStatus();
	_player[playerId].setMoving(true);
}

/*void	Game::explore(void) {
	if (SOLVING_ALGO == 0) {
		DepthFirstSearch::_depthFirstSearch(-1);
		std::cout << "Congratulations, player1 has collected " << _player[0].getNbCoins() << " coins." << std::endl;
	}
	else if (SOLVING_ALGO == 1) {
		std::cout << "Starting Dijkstra" << std::endl;
		//std::cout << dijkstra(0, 0, SIZE_X * SIZE_Y - 1) << std::endl;
		Dijkstra::dijkstra(0, SIZE_X - 1);
		Dijkstra::readDijkstraPath(0, SIZE_X - 1);
		usleep(Game->player[0].getMovingSpeedRate() * MAX_SPEED);
		//resetPath();
		Dijkstra::resetDijkstraTable();
		Display::_display(SIZE_X - 1);
		usleep(Game->player[0].getMovingSpeedRate() * MAX_SPEED);

		Dijkstra::dijkstra(SIZE_X - 1, SIZE_X * SIZE_Y - 1);
		Dijkstra::readDijkstraPath(SIZE_X - 1, SIZE_X * SIZE_Y - 1);
		usleep(Game->player[0].getMovingSpeedRate() * MAX_SPEED);
		//resetPath();
		Dijkstra::resetDijkstraTable();
		Display::_display(SIZE_X * SIZE_Y - 1);
		usleep(Game->player[0].getMovingSpeedRate() * MAX_SPEED);

		Dijkstra::dijkstra(SIZE_X * SIZE_Y - 1, (SIZE_X * SIZE_Y) - SIZE_X);
		Dijkstra::readDijkstraPath(SIZE_X * SIZE_Y - 1, SIZE_X * SIZE_Y - SIZE_X);
		usleep(Game->player[0].getMovingSpeedRate() * MAX_SPEED);
		//resetPath();
		Dijkstra::resetDijkstraTable();
		Display::_display(SIZE_X * SIZE_Y - SIZE_X);
		usleep(Game->player[0].getMovingSpeedRate() * MAX_SPEED);

		Dijkstra::dijkstra(SIZE_X * SIZE_Y - SIZE_X, 0);
		Dijkstra::readDijkstraPath(SIZE_X * SIZE_Y - SIZE_X, -1);
	}
	else if (SOLVING_ALGO == 2) {
		borderDijkstra(_player[0].getCell(), 1);
		borderDijkstra(_player[0].getCell(), 1);
		borderDijkstra(_player[0].getCell(), 1);
		borderDijkstra(_player[0].getCell(), 1);
	}
}*/

void	Game::display() {
	std::string	textColor;
	std::string	gridColor;
	std::string	numberColor;
	std::string	backColor = BACKBLACK;
	std::string	truenumberColor;
	std::string	text;
	double	x;
	double	y;
	//bool	player = false;

	/*std::cout << "test player position : " << std::endl;
	_player[0].getPosition().display();
	std::cout << ", " << _player[0].getOrientation() << std::endl;
	_player[1].getPosition().display();
	std::cout << ", " << _player[1].getOrientation() << std::endl;
	_player[2].getPosition().display();
	std::cout << ", " << _player[2].getOrientation() << std::endl;
	*/
	updateAll();
	if (_mode)
		gridColor = GREEN;
	else
		gridColor = MAGENTA;
	textColor = gridColor;
	std::cout << std::endl;
	std::cout << std::endl;
	std::cout << std::endl;
	for (int j = 0; j < 4 * SIZE_Y; ++j) {
		for (int i = 0; i < 4 * SIZE_X; ++i) {
			x = (i * 1.0 - 2) / 4;
			y = (j * 1.0 - 2) / 4;
			if (isInDeadZone(x, y) && i != 0 && j != 0)
				backColor = BACKRED;
			else
				backColor = BACKBLACK;
			text = " ";
			if (j % 4 == 0 and i % 4 != 0) {
				if (_maze.getCell()[Utils::xyToCellId(x, y, SIZE_X)].getWall(0))
					text = "__";
			}
			else if (j % 4 == 2 && i % 4 == 2) {
				if (_maze.getCell()[Utils::xyToCellId(x, y , SIZE_X)].getNbSeen() > 0 &&
						_maze.getCell()[Utils::xyToCellId(x, y , SIZE_X)].getNbSeen() < 4)
					text = ".";
				else if (_maze.getCell()[Utils::xyToCellId(x, y, SIZE_X)].getNbSeen() == 0) {
					if (_maze.getCell()[Utils::xyToCellId(x, y, SIZE_X)].getValue() == 0)
						text = "o";
					else
						text = _maze.getCell()[Utils::xyToCellId(x, y, SIZE_X)].getValue();
				}
			}
			if (i % 4 == 0 && j % 4 != 0) {
				if (_maze.getCell()[Utils::xyToCellId(x, y, SIZE_X)].getWall(3))
					text = "|";
			}
			if (playerIsOnSpot(0, x, y)) {
				text = getDirIcon(0);
				textColor = BOLDRED;
			}
			if (playerIsOnSpot(1, x, y)) {
				text = getDirIcon(1);
				textColor = BOLDYELLOW;
			}
			if (playerIsOnSpot(2, x, y)) {
				text = getDirIcon(2);
				textColor = BOLDCYAN;
			}
			Utils::printInColor(2, text, textColor, backColor);
			textColor = gridColor;
			text = " ";
		}
		if (j != 0)
			Utils::printInColor(2, "|", gridColor);
		std::cout << std::endl;
	}
	for (int i = 0; i < 4 * SIZE_X; ++i) {
		text = " ";
		if (i % 4 != 0)
			text = "__";
		Utils::printInColor(2, text, gridColor);
	}
	std::cout << std::endl;
	std::cout << std::endl;
}

bool	Game::playerIsOnSpot(int id, double x, double y) {
	return (Utils::samePoints(_player[id].getPosition(), Point(x, y), 0.25));
}

std::string	Game::getDirIcon(int id) {
	if (_player[id].getOrientation() == 0)
		return (">");
	else if (_player[id].getOrientation() == 90)
		return ("!");
	else if (_player[id].getOrientation() == -90)
		return ("^");
	else
		return ("<");
}
