#include "Group.h"
#include "ShapeFactory.h"

namespace experis
{

class ShapeFactory;

Group::Group()
: m_shapes{}
, m_brushForGroup{ascii::ColoredCanvas::WHITE}
{
}

Group::Group(const Group& a_other)
: m_brushForGroup{' '}
, m_shapes{}
{
	for(Shape *shape : a_other.m_shapes)
	{
		this->m_shapes.push_back(shape); //Todo add Clone func!!!
	}
}

Group& Group::operator=(const Group& a_other)
{
	m_brushForGroup = a_other.m_brushForGroup;
	m_shapes = a_other.m_shapes;
	return *this;
}

Group::~Group()
{
	for (Shape* shape : m_shapes)
	{
		delete shape;
	}
}

Group& Group::Add(Group& a_groupToCopy)
{
	for(Shape *shape : a_groupToCopy.m_shapes)
	{
		this->m_shapes.push_back(shape);
	}
	a_groupToCopy.m_shapes.clear();
	return *this;
}

void Group::MoveBy(const MoveByType deltaX, const MoveByType deltaY) 
{
	for (Shape *shape : m_shapes)
	{
		shape->MoveBy(deltaX, deltaY);
	}
}

void Group::DrawGroup(ascii::ColoredCanvas& a_canvas) const
{
	for (Shape *shape : m_shapes)
	{
		shape->DrawGroup(a_canvas);
	}
}

void Group::SetBrush(const char a_brush)
{
	for (Shape* shape : m_shapes)
	{
		shape->SetBrush(a_brush);
	}	
}

void SavePainting(const FilePath& a_path, const Group& a_image)
{
	std::ofstream outFile(a_path);
	for (const Shape* shape : a_image.m_shapes)
	{
		outFile << shape->EncodeShape() << "\n";
	}
}

Group LoadPainting(const FilePath& a_path, const experis::ShapeFactory& a_shapeFactory)
{
	Group loadedPrint{};
	class ShapeFactory;

	std::unordered_map<std::string, short> shapeMap = {
        {"Line", 1},
        {"Rectangle", 2},
        {"Square", 3},
        {"Circle", 4}
    };
	
	std::ifstream inFile(a_path);
	std::string line{};
	while (std::getline(inFile, line))
	{
		a_shapeFactory.CreateShape(line, loadedPrint);
		/*
		ShapeNumber shapeNumber = shapeMap.at((values.at(0)));
		
		}*/
	}
	return loadedPrint;
}

} //namespace experis