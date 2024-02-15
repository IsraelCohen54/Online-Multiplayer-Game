#include "Shape.h"

namespace experis
{

class MoveDown
{
public:
	explicit MoveDown();	
	MoveDown(const MoveDown& a_other) = default;
	MoveDown& operator=(const MoveDown& a_other) = delete;
	~MoveDown() = default;

	void operator()(Shape& a_shape);
};

} // experis namespace

