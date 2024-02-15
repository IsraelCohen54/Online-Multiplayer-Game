#include "CreateRectangle.h"
#include "Group.h"
#include "Rectangle.h"
#include "Point.h"

namespace experis
{
CreateRectangle::CreateRectangle()
{
}

void CreateRectangle::CreateShape(experis::Group& a_group, const std::vector<std::string>& a_values) const
{
	a_group.Add<Rectangle, Point, Point>(Point{short(std::stoul(a_values.at(1))), short(std::stoul(a_values.at(2)))},
				Point{short(std::stoul(a_values.at(3))), short((std::stoul(a_values.at(4))))},
				ChoseClrByVal(std::stoi(a_values.at(5))),
				ChoseClrByVal(std::stoi(a_values.at(6))),
				a_values.at(7)[0]);
}

} // experis namespace