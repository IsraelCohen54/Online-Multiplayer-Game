#pragma once
#include "Rectangle.h"
#include "Point.h"

namespace experis
{

class Square : public Rectangle
{
	using MoveByType = short;

public:
	explicit Square() = delete;
	Square(const Square& a_other) = delete;
	explicit Square(const Point a_upLeftPoint, const Point a_downRightPoint);
	explicit Square(const Point a_upLeftPoint, const Point a_downRightPoint, ascii::ColoredCanvas::Color a_bg, ascii::ColoredCanvas::Color a_fg, const char a_char);
	Square& operator=(const Square& a_other) = delete;
	virtual ~Square() override = default;

	//Todo ~~~ add __noexpect__ for all funcs, check out include needed! ~~~
	virtual void SetBrush(const char a_brush) override;
	virtual void SetFg(const ascii::ColoredCanvas::Color a_fg) override;
	virtual void SetBg(const ascii::ColoredCanvas::Color a_bg) override;
	virtual void MoveBy(const MoveByType deltaX, const MoveByType deltaY) override;
	virtual void DrawGroup(ascii::ColoredCanvas& a_canvas) const override;

	virtual std::string EncodeShape() const override;

	void ValidateSquare();

private:
	char m_brush;
	Point m_upLeftPoint;
	Point m_downRightPoint;
	ascii::ColoredCanvas::Color m_bg;
	ascii::ColoredCanvas::Color m_fg;
};

} //namespace experis