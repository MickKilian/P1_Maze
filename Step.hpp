#ifndef STEP_H
#define STEP_H

#include "Point.hpp"
#include <time.h>		//time_t, struct tm, difftime, time, mktime

class	Step {
	public:
		Step();
		Step(Point, double, double, time_t);
		~Step();
		Point	getPoint();
		double	getOrientation();
		double	getSpeed();
		int		getTime();
		void	setPoint(Point);

	private:
		Point	_point;
		double	_orientation;	//between 0-360deg + clopckwise, Odeg is UP (in the direciton positive y-axis)
		double	_speed;
		time_t	_time;
};

#endif // STEP_H
