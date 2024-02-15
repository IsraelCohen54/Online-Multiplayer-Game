#include "CreateCircle.h"
#include "Circle.h"
#include "Group.h"

namespace experis
{
CreateCircle::CreateCircle()
{
}

void CreateCircle::CreateShape(Group& a_group, const std::vector<std::string>& a_values) const
{
	a_group.Add<Circle, Point, double>(
				Point{short(std::stod(a_values.at(1))), short((std::stod(a_values.at(2))))},
				std::stod(a_values.at(3)),
				ChoseClrByVal(std::stoi(a_values.at(4))),
				ChoseClrByVal(std::stoi(a_values.at(5))),
				a_values.at(6)[0]);
}

} // experis namespace