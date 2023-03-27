#ifndef PLAYER_H
#define PLAYER_H

#include "Path.hpp"
#include "Route.hpp"
#include <string>

#define	PLAYER_STRATEGY		0		//strategy for all players

class	Player {
	public:
		Player();
		Player(int, int, double, double, double, int, int, int, int, int, int, int, int);
		~Player(void);
		int			getId(void);
		int			getType(void);
		double		getX(void);
		double		getY(void);
		double		getOrientation(void);
		//int			getCell(void);
		int			getNbCoins(void);
		int			getLives(void);
		//int			getMode(void);
		int			getMovingSpeedRate(void);
		int			getMaxSpeed(void);
		int			getStrategy(void);
		int			getStartingCell(void);
		int			getSizeX(void);
		int			getSizeY(void);
		Route		getRoute(void);
		void		setId(int);
		void		setType(int);
		void		setX(double x);
		void		setY(double y);
		void		setOrientation(double orientation);
		//void		setCell(int);
		void		setNbCoins(int);
		void		setLives(int);
		//void		setMode(int);
		void		setMovingSpeedRate(int);
		void		setMaxSpeed(int);
		void		setStrategy(int);
		void		setRoute(Route);

	private:
		int			_id;				//id of the player
		int			_type;				//0: master, 1: friend, 2: opponent
		double		_x;					//current x-coordinate in the maze
		double		_y;					//current y-coordinate in the maze
		double		_orientation;		//orientation of the player (in degrees between 0deg-UP and 360deg, positive clockwise)
//		int			_cell;				//position (cell id) in the maze
		int			_nbcoins;			//nb of collectd coins
		int			_lives;				//number of remaining lives
		//int		mode;
		int			_movingSpeedRate;	//current speed
		double		_maxSpeed;			//allowed maximum speed
		int			_strategy;			//current chosen strategy
		int			_startingCell;		//starting cell
		int			_sizeX;				//dimension of maze in x_direction
		int			_sizeY;				//dimension of maze in y_direction
		Route		_route;				//planned succcesion of cells for the future
		Path		_path;				//current path
};

#endif // PLAYER_H
