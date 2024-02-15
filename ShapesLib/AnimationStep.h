#pragma once
#include <vector>
#include "Shape.h"

namespace experis
{

class AnimationStep
{
public:
	explicit AnimationStep();
	AnimationStep(const AnimationStep& a_other) = delete;
	AnimationStep& operator=(const AnimationStep& a_other) = delete;
	virtual ~AnimationStep() = default;

	virtual bool ExecuteAnimation() = 0;
};

} // namespace experis