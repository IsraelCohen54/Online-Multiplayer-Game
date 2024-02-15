#pragma once

#include <string>
#include "ascii/colored_canvas.hpp"

namespace experis
{
using MoveByType = short;

class Shape
{
public:
	explicit Shape();
	Shape(const Shape& a_other);
	Shape& operator=(const Shape& a_other) = delete;
	virtual ~Shape() = default;

	virtual void SetBrush(const char a_brush) = 0;
	virtual void MoveBy(const MoveByType a_deltaX, const MoveByType a_deltaY) = 0;
	virtual void DrawGroup(ascii::ColoredCanvas& a_canvas) const = 0;

	virtual std::string EncodeShape() const = 0;
};

} //namespace experis