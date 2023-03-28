#ifndef PLAYER_H
#define PLAYER_H

#include "Utils.hpp"
#include "Path.hpp"
#include "Route.hpp"
#include "Action.hpp"
#include "Movement.hpp"
#include <string>

#define	PLAYER_STRATEGY		0		//strategy for all players

class	Player {
	public:
		Player();
		Player(int, int, Point, double, int, int, int, int, int, int, int, int, double, bool, double, bool, unsigned);
		~Player(void);
		int			getId(void);
		int			getType(void);
		Point		getPosition(void);
		double		getOrientation(void);
		int			getNbCoins(void);
		int			getLives(void);
		int			getMovingSpeedRate(void);
		int			getMaxSpeed(void);
		int			getStrategy(void);
		int			getStartingCell(void);
		int			getSizeX(void);
		int			getSizeY(void);
		Route		getRoute(void);
		Path		getPath(void);
		double		getDimInc(void);
		bool		getForceForward(void);
		double		getTolerance(void);
		Action		getAction(void);
		bool		getMoving(void);
		Movement	getMovement(void);
		unsigned	getIndexInPath(void);
		void		setId(int);
		void		setType(int);
		void		setPosition(Point);
		void		setOrientation(double orientation);
		void		setNbCoins(int);
		void		setLives(int);
		void		setMovingSpeedRate(int);
		void		setMaxSpeed(int);
		void		setStrategy(int);
		void		setStartingCell(int);
		void		setRoute(Route);
		void		setPath(Path);
		void		setDimInc(double);
		void		setAction(Action);
		void		setMoving(bool);
		void		setMovement(Movement);
		void		setIndexInPath(unsigned);
		Path		calcPath(Route, int);
		void		printStatus();
		void		move();
		void		updateOrientPosition(Point, double);
		void		updateAction();

	private:
		int			_id;				//id of the player
		int			_type;				//0: master, 1: friend, 2: opponent
		Point		_position;			//current location in maze
//		double		_x;					//current x-coordinate in the maze
//		double		_y;					//current y-coordinate in the maze
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
		double		_dimInc;			//distance increment on path
		bool		_forceForward;		//0: can go backwards, 1: can only go forward
		double		_tolerance;			//dist in mm under which two points are considered the same
		Route		_route;				//planned succcesion of cells for the future
		Path		_path;				//current path
		Action		_action;			//action
		Movement	_movement;			//movement
		bool		_moving;			//0: path is being travelled, movement is finished
		unsigned	_indexInPath;		//index >= 0 means that player is currently at this index in path
};

#endif // PLAYER_H
