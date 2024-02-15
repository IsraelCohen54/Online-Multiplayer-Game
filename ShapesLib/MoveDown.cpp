#include "MoveDown.h"
namespace experis
{

MoveDown::MoveDown()
{
}

void MoveDown::operator()(Shape& a_shape)
{
	a_shape.MoveBy(0, 1);
}

} //namespace experis