#pragma once
#include "Shape.h"

namespace experis
{

class MoveLeft
{
public:
	explicit MoveLeft();
	MoveLeft(const MoveLeft& a_other) = default;
	MoveLeft& operator=(const MoveLeft& a_other) = delete;
	~MoveLeft() = default;

	void operator()(Shape& a_shape);
};

} // experis namespace

