#include "MoveLeft.h"

namespace experis
{

MoveLeft::MoveLeft()
{
}

void MoveLeft::operator()(Shape& a_shape)
{
	a_shape.MoveBy(-1, 0);
}

} //namespace experis