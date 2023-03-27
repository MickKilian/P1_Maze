#ifndef STEP_H
#define STEP_H

#include <time.h>		//time_t, struct tm, difftime, time, mktime
						//
class	Step {
	public:
		Step();
		Step(double, double, double, double, time_t);
		~Step();
		double	getX();
		double	getY();
		double	getOrientation();
		double	getSpeed();
		int		getTime();

	private:
		double	_x;
		double	_y;
		double	_orientation;	//between 0-360deg + clopckwise, Odeg is UP (in the direciton positive y-axis)
		double	_speed;
		time_t	_time;
};

#endif // STEP_H
