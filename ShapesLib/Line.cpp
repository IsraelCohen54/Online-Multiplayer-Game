#include "Line.h"

namespace experis
{

Line::Line(const Point a_startPoint, const Point a_endPoint)
: ShapeOnCanvas{}
, m_start{a_startPoint}
, m_end{a_endPoint}
, m_bg{ascii::ColoredCanvas::Color::WHITE} // default color
, m_fg{ascii::ColoredCanvas::Color::WHITE} // default color
, m_brush{'0'}
{
}

Line::Line(const Point a_startPoint, const Point a_endPoint, Color a_bg, Color a_fg, const char a_char)
: ShapeOnCanvas{}
, m_start{a_startPoint}
, m_end{a_endPoint}
, m_bg{a_bg}
, m_fg{a_fg}
, m_brush{a_char}
{
}

void Line::SetBrush(const char a_brush)
{
	this->m_brush = a_brush;
}

void Line::SetFg(const ascii::ColoredCanvas::Color a_fg)
{
	m_fg = a_fg;
}

void Line::SetBg(const ascii::ColoredCanvas::Color a_bg)
{
	m_bg = a_bg;
}

void Line::MoveBy(const MoveByType deltaX, const MoveByType deltaY)
{
	this->m_start.MoveBy(deltaX, deltaY);
	this->m_end.MoveBy(deltaX, deltaY);
}

void Line::MoveByRightPoint(const MoveByType deltaX, const MoveByType deltaY)
{
	this->m_end.MoveBy(deltaX, deltaY);
}

void Line::DrawGroup(ascii::ColoredCanvas& a_canvas) const
{
	ascii::DrawLine(a_canvas, m_brush, m_fg, m_bg, m_start, m_end);
}

std::string Line::EncodeShape() const
{
    std::string encodedStr{};
	encodedStr += "Line";
    encodedStr += ",";
    encodedStr += std::to_string(m_start.GetX());
    encodedStr += ",";
    encodedStr += std::to_string(m_start.GetY());
    encodedStr += ",";
    encodedStr += std::to_string(m_end.GetX());
    encodedStr += ",";
    encodedStr += std::to_string(m_end.GetY());
    encodedStr += ",";
    encodedStr += std::to_string(m_bg);
    encodedStr += ",";
    encodedStr += std::to_string(m_fg);
    encodedStr += ",";
    encodedStr += m_brush;

	return encodedStr;
}

} // experis namespace