#ifndef UTILS_H
#define UTILS_H

#include "Maze.hpp"
#include "Route.hpp"
#include "Point.hpp"
#include <string>
#include <iostream>
#include <cmath>		//math library

#define	BACKBLACK		"\x1b[40m"
#define	BACKRED			"\x1b[41m"
#define	BLACK			"\x1b[30m"
#define	RED				"\x1b[31m"
#define	BOLDRED			"\x1b[31;1m"
#define	GREEN			"\x1b[32m"
#define	BOLDGREEN		"\x1b[32;1m"
#define	YELLOW			"\x1b[33m"
#define	BOLDYELLOW		"\x1b[33;1m"
#define	BLUE			"\x1b[34m"
#define	MAGENTA			"\x1b[35m"
#define	BOLDMAGENTA		"\x1b[35;1m"
#define	CYAN			"\x1b[36m"
#define	BOLDCYAN		"\x1b[36;1m"
#define	WHITE			"\x1b[37m"
#define	RESET			"\x1b[0m"

# define M_PI			3.14159265358979323846  /* pi */
# define CLOSE_ENOUGH	1	//dist in mm under which 2 points are considered equal

class	Utils {
	public:
		static std::string		getColor(int);
		static double			min(double, double);
		static double			max(double, double);
		static double			dist(Point, Point);
		static double			abAngle(Point, Point);
		static bool				samePoints(Point, Point, double);
		static double			modulo360(double);
		static int				xyToCellId(double, double, int);
		static double			cellIdToX(int, int);
		static double			cellIdToY(int, int);
		static int				getIdWithDir(int, int, int);
		static int				findDirWithId(int, int, int);
		static Point			cellIdToPoint(int, int);
		static int				pointToCellId(Point, int);
		static void				printInColor(int, std::string = " ", std::string = BLACK, std::string = BACKBLACK);

	private:
};

#endif // UTILS_H
