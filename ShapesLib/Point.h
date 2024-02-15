#pragma once

#include "ascii/point.hpp"

class Point {
public:
	using CoordType = short;
	//using CoordType = int;

	//typedef short CoordType;
	Point(CoordType a_x, CoordType a_y) : m_x(a_x), m_y(a_y) { }
	Point(const Point& a_other) = default;
	Point(const Point& a_other, CoordType a_xOffset, CoordType a_yOffset) : m_x(a_other.m_x + a_xOffset), m_y(a_other.m_y + a_yOffset) { }
	Point& operator=(const Point& a_other) = default;
	~Point() = default;

	Point& MoveBy(CoordType a_deltaX, CoordType a_deltaY) { m_x += a_deltaX; m_y += a_deltaY; return *this; }
	Point& RotateAround(CoordType a_rotationCenterX, CoordType a_rotationCenterY, double a_degrees);
	Point GetMovedBy(CoordType a_deltaX, CoordType a_deltaY) const { return Point(m_x + a_deltaX, m_y + a_deltaY); }
	Point GetRotatedAround(CoordType a_rotationCenterX, CoordType a_rotationCenterY, double a_degrees) const;

	CoordType GetX() const { return m_x;  }
	CoordType GetY() const { return m_y;  }
	operator ascii::Point() const { return ascii::Point{m_x, m_y}; }

private:
	CoordType m_x;
	CoordType m_y;
};