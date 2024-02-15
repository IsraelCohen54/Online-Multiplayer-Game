#include "Square.h"


namespace experis
{

Square::Square(const Point a_upLeftPoint, const Point a_downRightPoint)
: //ShapeOnCanvas{}
  Rectangle{a_upLeftPoint, a_downRightPoint}
, m_upLeftPoint{a_upLeftPoint}
, m_downRightPoint{a_downRightPoint}
, m_bg{ascii::ColoredCanvas::Color::WHITE} // default color
, m_fg{ascii::ColoredCanvas::Color::WHITE} // default color
, m_brush{'0'}
{
	ValidateSquare();
}

Square::Square(const Point a_upLeftPoint, const Point a_downRightPoint, ascii::ColoredCanvas::Color a_bg, ascii::ColoredCanvas::Color a_fg, const char a_char)
: //ShapeOnCanvas{}
  Rectangle{a_upLeftPoint, a_downRightPoint}
, m_upLeftPoint{a_upLeftPoint}
, m_downRightPoint{a_downRightPoint}
, m_bg{a_bg}
, m_fg{a_fg}
, m_brush{a_char}
{
	ValidateSquare();
}

void Square::SetBrush(const char a_brush)
{
	this->m_brush = a_brush;
}

void Square::SetFg(const ascii::ColoredCanvas::Color a_fg)
{
	m_fg = a_fg;
}

void Square::SetBg(const ascii::ColoredCanvas::Color a_bg)
{
	m_bg = a_bg;
}

void Square::MoveBy(const MoveByType deltaX, const MoveByType deltaY)
{
	this->m_upLeftPoint.MoveBy(deltaX, deltaY);
	this->m_downRightPoint.MoveBy(deltaX, deltaY);
}

void Square::DrawGroup(ascii::ColoredCanvas& a_canvas) const
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

struct SquareFormatException : std::exception
{
    SquareFormatException(const char *a_msg, Point a_start, Point a_end);
    const char *m_msg;
    Point m_start;
	Point m_end;
};

SquareFormatException::SquareFormatException(const char *a_msg, Point a_start, Point a_end)
: m_msg{a_msg}
, m_start{a_start}
, m_end{a_end}
{
}

void Square::ValidateSquare()
{
	if ((m_upLeftPoint.GetX() - m_downRightPoint.GetX()) * (m_upLeftPoint.GetX() - m_downRightPoint.GetX())
		!= (m_upLeftPoint.GetY() - m_downRightPoint.GetY()) * (m_upLeftPoint.GetY() - m_downRightPoint.GetY()))
	{
		throw(SquareFormatException("wrong size", m_upLeftPoint, m_downRightPoint));
	}
}

std::string Square::EncodeShape() const
{
	std::string encodedStr{};
	encodedStr += "Square";
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
