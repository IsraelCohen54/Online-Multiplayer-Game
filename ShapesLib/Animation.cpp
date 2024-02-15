#include "Animation.h"

namespace experis
{

Animation::Animation()
: m_animations{}
{
}

void Animation::Add(AnimationStep *a_animation)
{
	this->m_animations.push_back(a_animation);
}

void Animation::ExecuteAnimation()
{
	bool hasAnimeMoves = false;
	for( auto &an : this->m_animations)
	{
		hasAnimeMoves = an->ExecuteAnimation();
		if (hasAnimeMoves)
		{
			break;
		}
	}
	if (!hasAnimeMoves)
	{
		this->m_animations.clear();
	}
}

bool Animation::HasAnimation()
{
	return m_animations.size();
}

Animation::~Animation()
{
	for (AnimationStep* an : m_animations)
	{
		delete an;
	}
}

} //namespace experis 