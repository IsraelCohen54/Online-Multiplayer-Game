#include <cmath>
#include <corecrt_math.h>
#include "Point.h"

using namespace std;

static const double PI = 2.0 * acos(0.0);

Point& Point::RotateAround(CoordType a_rotationCenterX, CoordType a_rotationCenterY, double a_degrees)
{
	*this = GetRotatedAround(a_rotationCenterX, a_rotationCenterY, a_degrees);
	return *this;
}

Point Point::GetRotatedAround(CoordType a_rotationCenterX, CoordType a_rotationCenterY, double a_degrees) const
{
	double radians = PI * a_degrees / 180.0;
	CoordType originedX = m_x - a_rotationCenterX;
	CoordType originedY = m_y - a_rotationCenterY;
	double newX = originedX * cos(radians) - originedY * sin(radians);
	double newY = originedY * cos(radians) + originedX * sin(radians);
	return Point{ short(newX) + a_rotationCenterX, short(newY) + a_rotationCenterY };
}