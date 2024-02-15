#include "Rectangle.h"


namespace experis
{

Rectangle::Rectangle(const Point a_upLeftPoint, const Point a_downRightPoint)
: ShapeOnCanvas{}
, m_upLeftPoint{a_upLeftPoint}
, m_downRightPoint{a_downRightPoint}
, m_bg{ascii::ColoredCanvas::Color::WHITE} // default color
, m_fg{ascii::ColoredCanvas::Color::WHITE} // default color
, m_brush{'0'}
{
}

Rectangle::Rectangle(const Point a_upLeftPoint, const Point a_downRightPoint, ascii::ColoredCanvas::Color a_bg, ascii::ColoredCanvas::Color a_fg, const char a_char)
: ShapeOnCanvas{}
, m_upLeftPoint{a_upLeftPoint}
, m_downRightPoint{a_downRightPoint}
, m_bg{a_bg}
, m_fg{a_fg}
, m_brush{a_char}
{
}

void Rectangle::SetBrush(const char a_brush)
{
	this->m_brush = a_brush;
}

void Rectangle::SetFg(const ascii::ColoredCanvas::Color a_fg)
{
	m_fg = a_fg;
}

void Rectangle::SetBg(const ascii::ColoredCanvas::Color a_bg)
{
	m_bg = a_bg;
}

void Rectangle::MoveBy(const MoveByType deltaX, const MoveByType deltaY)
{
	this->m_upLeftPoint.MoveBy(deltaX, deltaY);
	this->m_downRightPoint.MoveBy(deltaX, deltaY);
}

void Rectangle::DrawGroup(ascii::ColoredCanvas& a_canvas) const
{
	ascii::DrawLine(a_canvas, m_brush, m_fg, m_bg
		// left line:
		, m_upLeftPoint.GetX(), m_upLeftPoint.GetY()
		, m_upLeftPoint.GetX(), m_downRightPoint.GetY());
	ascii::DrawLine(a_canvas, m_brush, m_fg, m_bg
		// upper line:
		, m_upLeftPoint.GetX(), m_upLeftPoint.GetY()
		, m_downRightPoint.GetX(), m_upLeftPoint.GetY());
	ascii::DrawLine(a_canvas, m_brush, m_fg, m_bg
		// buttom line:
		, m_upLeftPoint.GetX(), m_downRightPoint.GetY()
		, m_downRightPoint.GetX(), m_downRightPoint.GetY());	    
	ascii::DrawLine(a_canvas, m_brush, m_fg, m_bg
		// right line:
		, m_downRightPoint.GetX(), m_upLeftPoint.GetY()
		, m_downRightPoint.GetX(), m_downRightPoint.GetY());
}

std::string Rectangle::EncodeShape() const
{
    std::string encodedStr{};
	encodedStr += "Rectangle";
    encodedStr += ",";
    encodedStr += std::to_string(m_upLeftPoint.GetX());
    encodedStr += ",";
    encodedStr += std::to_string(m_upLeftPoint.GetY());
    encodedStr += ",";
    encodedStr += std::to_string(m_downRightPoint.GetX());
    encodedStr += ",";
    encodedStr += std::to_string(m_downRightPoint.GetY());
    encodedStr += ",";
    encodedStr += std::to_string(m_bg);
    encodedStr += ",";
    encodedStr += std::to_string(m_fg);
	encodedStr += ",";
	encodedStr += m_brush;

	return encodedStr;
}

} // experis namespace
