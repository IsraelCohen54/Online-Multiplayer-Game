#include "MoveUp.h"

namespace experis
{

MoveUp::MoveUp()
{
}

void MoveUp::operator()(Shape& a_shape)
{
	a_shape.MoveBy(0, -1);
}

} //namespace experis
