#ifndef ACTION_H
#define ACTION_H

#include "Point.hpp"
#include "Utils.hpp"
#include <iostream>
#include <cmath>

class	Action {
	public:
		Action();
		Action(Point, double, Point, double, bool, double);
		~Action();
		double	getNewOrientation();
		double	getMaxSpeed();
		double	getAngleTurn();
		double	getTransGo();
		void	setPosition(Point);
		void	setOrientation(double);
		void	setNewOrientation(double);
		void	setTarget(Point);
		void	setAngleTurn(double);
		void	setTransGo(double);
		void	decision(Point);
		void	turn(double, double);
		void	go(double, double);
		void	display();

	private:
		Point	_position;			//current position of player
		double	_orientation;		//current orientation of player
		Point	_target;			//next location target of player
		double	_newOrientation;	//current orientation of player
		double	_maxSpeed;			//max allowed speed
		bool	_forceForward;		//0: can go backwards, 1: can only go forward
		double	_tolerance;			//dist in mm under which two points are considered the same
		double	_angleTurn;			//next rotation in deg
		double	_transGo;			//next translation in mm
};

#endif // ACTION_H
