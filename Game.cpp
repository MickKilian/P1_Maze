/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbourgeo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/27 03:03:58 by mbourgeo          #+#    #+#             */
/*   Updated: 2023/03/27 10:46:54 by mbourgeo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Game.hpp"

Game::Game() : _mode(0), _nbPlayers(NB_PLAYERS), _totalGameTime(TOTAL_GAME_TIME),
	_shrinkingSpeed(SHRINKING_SPEED), _remainingCoins(SIZE_X * SIZE_Y) {
	_maze = Maze(SIZE_X, SIZE_Y);
	for (int i = 0; i < _nbPlayers; ++i) {
		_player.push_back(Player(i, 0, Utils::cellIdToX(INITIAL_CELL, SIZE_X), Utils::cellIdToY(INITIAL_CELL, SIZE_X),
			INITIAL_ORIENTATION, 0, 1, 1, MAX_SPEED, PLAYER_STRATEGY, INITIAL_CELL, SIZE_X, SIZE_Y));
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
	_maze.dijkstra(0, SIZE_X - 1);
	//_maze.displayDijkstraTable();
	//std::cout << std::endl;
	//std::cout << "Initial size of Player's root is : " <<  _player[0].getRoute().getCell().size() << std::endl;
	//std::cout << "First element of Player's root is : " <<  _player[0].getRoute().getCell()[0] << std::endl;
	//_player[0].setRoute(_maze.readDijkstraPath(0, SIZE_X - 1, _player[0].getRoute()));
	std::cout << std::endl;
	//_player[0].getRoute().display();
	//std::cout << "route size : " << _player[0].getRoute().getCell().size() << std::endl;
	_maze.resetDijkstraTable();
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
			Utils::printInColor(2, text, textColor, backColor);
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
