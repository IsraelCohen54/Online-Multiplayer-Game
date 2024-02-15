#pragma once

#include <vector>

#include "AnimationStep.h"
#include "AnimationMoveTo.h"

namespace experis
{

class Animation
{
public:
	explicit Animation();
	Animation(const Animation& a_other) = delete;
	Animation& operator=(const Animation& a_other) = delete;
	~Animation();

	void ExecuteAnimation();
	void Add(AnimationStep *a_animation); 
	bool HasAnimation();

private:
	std::vector<AnimationStep*> m_animations;
};

} // namespace experis



