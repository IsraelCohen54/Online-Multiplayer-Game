#include "Circle.h"

namespace experis
{

Circle::Circle(const Point a_middlePoint, const double a_radius)
: ShapeOnCanvas{}
, m_middle{a_middlePoint}
, m_raduis {a_radius}
, m_brush {'0'}
, m_bg{ascii::ColoredCanvas::Color::WHITE}
, m_fg{ascii::ColoredCanvas::Color::WHITE}
{
}

Circle::Circle(const Point a_middlePoint, const double a_radius, ascii::ColoredCanvas::Color a_bg, ascii::ColoredCanvas::Color a_fg, const char a_char)
: ShapeOnCanvas{}
, m_middle{a_middlePoint}
, m_raduis {a_radius}
, m_brush {a_char}
, m_bg{a_bg}
, m_fg{a_fg}
{
}

void Circle::SetFg(const ascii::ColoredCanvas::Color a_fg)
{
	this->m_fg = a_fg;
}

void Circle::SetBg(const ascii::ColoredCanvas::Color a_bg)
{
	this->m_bg = a_bg;
}

void Circle::SetBrush(const char a_brush)
{
	this->m_brush = a_brush;
}

void Circle::MoveBy(const MoveType deltaX, const MoveType deltaY)
{
	this->m_middle = this->m_middle.MoveBy(deltaX, deltaY);
}

void Circle::DrawGroup(ascii::ColoredCanvas& a_canvas) const
{
	ascii::DrawCircle(a_canvas, m_brush, m_fg, m_bg, m_middle, m_raduis);
}

std::string Circle::EncodeShape() const
{
    std::string encodedStr{};
	encodedStr += "Circle";
    encodedStr += ",";
    encodedStr += std::to_string(m_middle.GetX());
    encodedStr += ",";
    encodedStr += std::to_string(m_middle.GetY());
    encodedStr += ",";
    encodedStr += std::to_string(m_raduis);
    encodedStr += ",";
    encodedStr += std::to_string(m_bg);
    encodedStr += ",";
    encodedStr += std::to_string(m_fg);
    encodedStr += ",";
	encodedStr += m_brush;

	return encodedStr;
}

} // namespace experis