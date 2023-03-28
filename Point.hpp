#ifndef POINT_H
#define POINT_H

#include <iomanip>
#include <iostream>

class Point
{
	public:
		Point();
		Point(double, double);
		~Point();
		double	getX();
		double	getY();
		void	setX(double x);
		void	setY(double y);
		void	display();

	private:
		double	_x;
		double	_y;
};

/*class Line
{
    private:
        Point p1;
        Point p2;
    public:
        Line(const Point & p1, const Point & p2 ) : p1(p1), p2(p2) {}

        void setPoints( const Point & ap1, const Point & ap2)
        {
            p1 = ap1;
            p2 = ap2;
        }
}*/

#endif // ROUTE_H
