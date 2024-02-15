#pragma once
#include <string>
#include <unordered_map>
#include <memory>
#include "Creator.h"
#include "CreateLine.h"
#include "CreateRectangle.h"
#include "CreateCircle.h"
#include "CreateSquare.h"

namespace experis
{
class Group;

class ShapeFactory
{
public:
	ShapeFactory();
	ShapeFactory(const ShapeFactory& a_other) = delete;
	ShapeFactory& operator=(const ShapeFactory& a_other) = delete;
	~ShapeFactory() =  default;

	void CreateShape(const std::string& a_shapeStr, Group& a_group) const;
	void Register(const std::string& a_shapeEncodedString, std::unique_ptr<Creator> a_newCreator);

private:
	std::unordered_map<std::string, std::unique_ptr<Creator>> m_shapesFactory;
};

} // experis namespace

