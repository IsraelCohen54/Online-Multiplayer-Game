#pragma once

#include "Creator.h"
#include "Line.h"

namespace experis
{

class Group;

class CreateLine : public Creator
{
public:
	CreateLine();
	CreateLine(const CreateLine& a_other) = delete;
	CreateLine& operator=(const CreateLine& a_other) = delete;
	virtual ~CreateLine() = default;

	virtual void CreateShape(Group& a_group, const std::vector<std::string>& a_values) const override;
};

} // experis namespace
