#pragma once

#include "Point.h"
#include "ascii/colored_canvas.hpp"
#include "ShapeOnCanvas.h"
namespace experis
{

class Line : public ShapeOnCanvas
{
	using MoveByType = short;
	using Color = ascii::ColoredCanvas::Color;

public:
	explicit Line() = delete;
	Line(const Line& a_other) = delete;
	explicit Line(const Point a_startPoint, const Point a_endPoint);
	explicit Line(const Point a_startPoint, const Point a_endPoint, Color a_bg, Color a_fg, const char a_char);
	Line& operator=(const Line& a_other) = delete;
	virtual ~Line() override = default;

	//Todo ~~~ add __noexpect__ for all funcs, check out include needed! ~~~
	virtual void SetBrush(const char a_brush) override;
	virtual void SetFg(const ascii::ColoredCanvas::Color a_fg) override;
	virtual void SetBg(const ascii::ColoredCanvas::Color a_bg) override;
	virtual void MoveBy(const MoveByType deltaX, const MoveByType deltaY) override;
	virtual void DrawGroup(ascii::ColoredCanvas& a_canvas) const override;
	void MoveByRightPoint(const MoveByType deltaX, const MoveByType deltaY);

	virtual std::string EncodeShape() const override;

private:
	char m_brush;
	Point m_start;
	Point m_end;
	ascii::ColoredCanvas::Color m_bg;
	ascii::ColoredCanvas::Color m_fg;
};

} // experis namespace

