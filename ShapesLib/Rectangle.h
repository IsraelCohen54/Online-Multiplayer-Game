#pragma once
#include "ShapeOnCanvas.h"
#include "Point.h"

namespace experis
{

class Rectangle : public ShapeOnCanvas
{
	using MoveByType = short;

public:
	explicit Rectangle() = delete;
	Rectangle(const Rectangle& a_other) = delete;
	explicit Rectangle(const Point a_upLeftPoint, const Point a_downRightPoint);
	explicit Rectangle(const Point a_upLeftPoint, const Point a_downRightPoint, ascii::ColoredCanvas::Color a_bg, ascii::ColoredCanvas::Color a_fg, const char a_char);
	Rectangle& operator=(const Rectangle& a_other) = delete;
	virtual ~Rectangle() override = default;

	//Todo ~~~ add __noexpect__ for all funcs, check out include needed! ~~~
	virtual void SetBrush(const char a_brush) override;
	virtual void SetFg(const ascii::ColoredCanvas::Color a_fg) override;
	virtual void SetBg(const ascii::ColoredCanvas::Color a_bg) override;
	virtual void MoveBy(const MoveByType deltaX, const MoveByType deltaY) override;
	virtual void DrawGroup(ascii::ColoredCanvas& a_canvas) const override;

	virtual std::string EncodeShape() const override;

private:
	char m_brush;
	Point m_upLeftPoint;
	Point m_downRightPoint;
	ascii::ColoredCanvas::Color m_bg;
	ascii::ColoredCanvas::Color m_fg;
};

} //namespace experis