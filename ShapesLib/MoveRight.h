#pragma once
#include "Shape.h"

namespace experis
{

class MoveRight
{
public:
	explicit MoveRight();	
	MoveRight(const MoveRight& a_other) = default;
	MoveRight& operator=(const MoveRight& a_other) = delete;
	~MoveRight() = default;

	void operator()(Shape& a_shape);
};

} // experis namespace