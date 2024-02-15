#pragma once
#include "Creator.h"
#include "Rectangle.h"

namespace experis
{

class CreateRectangle : public Creator
{
class Group;

public:
	CreateRectangle();
	CreateRectangle(const CreateRectangle& a_other) = delete;
	CreateRectangle& operator=(const CreateRectangle& a_other) = delete;
	~CreateRectangle() =  default;

	virtual void CreateShape(experis::Group& a_group, const std::vector<std::string>& a_values) const override;

private:
	
};

} // experis namespace
