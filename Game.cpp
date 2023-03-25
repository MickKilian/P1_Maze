#include "Game.hpp"

Game::Game() : _nbPlayers(0), _curTime(0), _remainingCoins(0) {
}

Game::Game(int nbPlayers, time_t time, int coins) : _nbPlayers(nbPlayers), _curTime(time), _remainingCoins(coins) {
}

Game::~Game() {
}

int			Game::getNbPlayers(void) {
	return (_nbPlayers);
}

time_t		Game::getCurTime(void) {
	return(_curTime);
}

int			Game::getRemainingCoins(void) {
	return (_remainingCoins);
}

void		Game::getNbPlayers(int nbPlayers) {
	_nbPlayers = nbPlayers;
}

void		Game::getCurTime(time_t time) {
	_curTime = time;
}

void		Game::getRemainingCoins(int coins) {
	_remainingCoins = coins;
}
