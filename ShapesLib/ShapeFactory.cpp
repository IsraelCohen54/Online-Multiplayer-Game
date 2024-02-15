#include <sstream>
#include <cassert>
#include "ShapeFactory.h"
#include "spdlog/spdlog.h"

namespace experis
{
ShapeFactory::ShapeFactory() // can't be initialized currently with initialization list because of r-value dont go well with move
{
	m_shapesFactory.insert(std::make_pair(std::string{"Line"}, std::make_unique<CreateLine>()));
	m_shapesFactory.insert(std::make_pair(std::string{"Rectangle"}, std::make_unique<CreateRectangle>()));
	m_shapesFactory.insert(std::make_pair(std::string{"Square"}, std::make_unique<CreateSquare>()));
	m_shapesFactory.insert(std::make_pair(std::string{"Circle"}, std::make_unique<CreateCircle>()));
}

void ShapeFactory::CreateShape(const std::string& a_shapeStr, Group& a_group) const
{
	std::vector<std::string> values;
	std::stringstream ss(a_shapeStr);
	std::string value;
	while (std::getline(ss, value, ','))
	{
		values.push_back(value);
	}
	assert(!values.empty());
	
    // Get the shape encoded string (e.g., "CreateLine", "CreateRectangle", etc.)
    std::string shapeEncodedString = values.at(0);

    // Find the corresponding creator in the map
    std::unordered_map<std::string, std::unique_ptr<Creator>>::const_iterator creatorIt = m_shapesFactory.find(shapeEncodedString);
    if (creatorIt != m_shapesFactory.end())
    {
        creatorIt->second->CreateShape(a_group, values);
    }
    else
    {	
		spdlog::error("Wrong Shape name");
    }

}

void ShapeFactory::Register(const std::string& a_shapeEncodedString, std::unique_ptr<Creator> a_newCreator)
{
    m_shapesFactory.insert(std::make_pair(a_shapeEncodedString, std::move(a_newCreator)));
}

} // namespace experis