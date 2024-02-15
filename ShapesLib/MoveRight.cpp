#include "MoveRight.h"

namespace experis
{

MoveRight::MoveRight()
{
}

void MoveRight::operator()(Shape& a_shape)
{
	a_shape.MoveBy(1, 0);
}

} //namespace experis
