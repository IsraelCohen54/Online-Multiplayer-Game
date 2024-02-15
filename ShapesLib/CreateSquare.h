#pragma once
#include "Creator.h"
#include "Square.h"

namespace experis
{
class Group;

class CreateSquare : public Creator
{
public:
	CreateSquare();
	CreateSquare(const CreateSquare& a_other) = delete;
	CreateSquare& operator=(const CreateSquare& a_other) = delete;
	~CreateSquare() =  default;

	virtual void CreateShape(Group& a_group, const std::vector<std::string>& a_values) const override;

private:
	
};

} // experis namespace

