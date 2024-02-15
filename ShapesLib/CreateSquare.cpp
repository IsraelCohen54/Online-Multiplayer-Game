#include "CreateSquare.h"
#include "Group.h"

namespace experis
{

CreateSquare::CreateSquare()
{

}

void CreateSquare::CreateShape(Group& a_group, const std::vector<std::string>& a_values) const
{
	a_group.Add<Square, Point, Point>(
				Point{short(std::stoul(a_values.at(1))), short(std::stoul(a_values.at(2)))},
				Point{short(std::stoul(a_values.at(3))), short(std::stoul(a_values.at(4)))},
				ChoseClrByVal(std::stoi(a_values.at(5))),
				ChoseClrByVal(std::stoi(a_values.at(6))),
				a_values.at(7)[0]);
}

} // experis namespace