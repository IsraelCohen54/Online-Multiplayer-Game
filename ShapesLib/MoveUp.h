#pragma once
#include "Shape.h"

namespace experis
{

class MoveUp
{
public:
	explicit MoveUp();
	MoveUp(const MoveUp& a_other) = default;
	MoveUp& operator=(const MoveUp& a_other) = delete;
	~MoveUp() = default;

	void operator()(Shape& a_shape);
};

} // experis namespace

