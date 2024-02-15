#pragma once
#include "ascii/colored_canvas.hpp"
#include "Point.h"
#include "ShapeOnCanvas.h"

namespace experis
{

class Circle : public ShapeOnCanvas
{
	using MoveType = short;

public:
	explicit Circle() = delete;
	explicit Circle(const Point a_middlePoint, const double a_radius);
	explicit Circle(const Point a_middlePoint, const double a_radius, ascii::ColoredCanvas::Color a_bg, ascii::ColoredCanvas::Color a_fg, const char a_char);
	Circle(const Circle& a_other) = delete;
	Circle& operator=(const Circle& a_other) = delete;
	virtual ~Circle() override = default;

	virtual void SetFg(const ascii::ColoredCanvas::Color a_fg) override;
	virtual void SetBg(const ascii::ColoredCanvas::Color a_bg) override;
	virtual void SetBrush(const char a_brush) override;
	virtual void MoveBy(const MoveType deltaX, const MoveType deltaY) override;
	virtual void DrawGroup(ascii::ColoredCanvas& a_canvas) const override;

	virtual std::string EncodeShape() const override;

private:
	Point m_middle;
	double m_raduis;
	char m_brush;
	ascii::ColoredCanvas::Color m_bg;
	ascii::ColoredCanvas::Color m_fg;
};

} // experis namespace