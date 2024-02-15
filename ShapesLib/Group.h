#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>
#include <unordered_map>

#include "Rectangle.h" // todo try to pass to cpp and declare class here...
#include "ascii/colored_canvas.hpp"
#include "ShapeOnCanvas.h"

namespace experis
{
using ChoseClrByVal = ascii::ColoredCanvas::Color;

using FilePath = std::string;

class Group;
void SavePainting(const FilePath& a_path, const Group& a_image);
class ShapeFactory;
Group LoadPainting(const FilePath& a_path, const ShapeFactory& a_shapeFactory);

class Group : public Shape
{	
	friend void SavePainting(const FilePath& a_path, const Group& a_image);
	friend Group LoadPainting(const FilePath& a_path, const ShapeFactory& a_shapeFactory);

public:
	explicit Group();
	Group(const Group& a_other);
	Group& operator=(const Group& a_other);
	virtual ~Group() override;

	Group& Add(Group& a_groupToCopy);

	template<typename ObjectType, typename ValType1, typename ValType2>
	ObjectType& Add(ValType1 a_val1, ValType2 a_val2)
	{
		ObjectType *shape = new ObjectType{a_val1, a_val2};
		m_shapes.push_back(shape);
		return *shape;
	}

	template<typename ObjectType, typename ValType1, typename ValType2>
	ObjectType& Add(ValType1 a_val1, ValType2 a_val2, ascii::ColoredCanvas::Color a_bg, 
		ascii::ColoredCanvas::Color a_fg, const char a_char)
	{
		ObjectType *shape = new ObjectType{a_val1, a_val2, a_bg, a_fg, a_char};
		m_shapes.push_back(shape);
		return *shape;
	}
	
	virtual void MoveBy(const MoveByType deltaX, const MoveByType deltaY) override;
	virtual void DrawGroup(ascii::ColoredCanvas& a_canvas) const override;
	virtual void SetBrush(const char a_brush) override;

	virtual std::string EncodeShape() const override{ return std::string{"should not be used actually, as Group encoding only to be written to a file\n"};}

private:
	char m_brushForGroup;
	std::vector<Shape*> m_shapes;
};

} // namespace experis 