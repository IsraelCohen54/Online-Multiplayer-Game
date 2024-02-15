#pragma once
#include "AnimationStep.h"
#include "Shape.h"

namespace experis
{
template<typename T>
class AnimationMoveTo : public AnimationStep
{
public:
	explicit AnimationMoveTo() // for animation member and Add new method
	: AnimationStep{}
	, m_moveToDirection{}
	, m_steps{}
	, m_shape{}
	{
	}
	explicit AnimationMoveTo(Shape &a_shape, const unsigned int a_steps, T a_moveToDirection)
	: AnimationStep{}
	, m_moveToDirection{a_moveToDirection}
	, m_steps{a_steps}
	, m_shape{a_shape}
	{
	}
	AnimationMoveTo(const AnimationMoveTo& a_other) = delete;
	AnimationMoveTo& operator=(const AnimationMoveTo& a_other) = delete;
	~AnimationMoveTo() = default;

	virtual bool ExecuteAnimation() override
	{
	if (m_steps != 0)
	{
		m_moveToDirection.operator()(m_shape);
		--m_steps;
		return true;
	}
	return false;
}

private:
	T m_moveToDirection;
	unsigned int m_steps;
	Shape &m_shape;
};

} // namespace experis