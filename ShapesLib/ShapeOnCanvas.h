#pragma once
#include "ascii/colored_canvas.hpp"
#include "Shape.h"

namespace experis
{
using MoveByType = short;

class ShapeOnCanvas : public Shape
{
public:
	explicit ShapeOnCanvas();
	ShapeOnCanvas(const ShapeOnCanvas& a_other) = delete;
	ShapeOnCanvas& operator=(const ShapeOnCanvas& a_other) = delete;
	virtual ~ShapeOnCanvas() = default;
	
	virtual void SetBrush(const char a_brush) = 0;
	virtual void SetFg(const ascii::ColoredCanvas::Color a_fg) = 0;
	virtual void SetBg(const ascii::ColoredCanvas::Color a_bg) = 0;
	virtual void MoveBy(const MoveByType deltaX, const MoveByType deltaY) = 0;
	virtual void DrawGroup(ascii::ColoredCanvas& a_canvas) const = 0;
	virtual std::string EncodeShape() const = 0;
};

} //namespace experis