#pragma once
#include "Creator.h"
#include "Line.h"


namespace experis
{
class Group;

class CreateCircle : public Creator
{
public:
	CreateCircle();
	CreateCircle(const CreateCircle& a_other) = delete;
	CreateCircle& operator=(const CreateCircle& a_other) = delete;
	~CreateCircle() =  default;

	virtual void CreateShape(Group& a_group, const std::vector<std::string>& a_values) const override;
};

} // experis namespace
