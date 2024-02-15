#pragma once

#include <memory>

namespace experis
{
class Player;

class Action
{
public:
	explicit Action() = default;
	Action(const Action& a_other) = delete;
	Action& operator=(const Action& a_other) = delete;
	virtual ~Action() = default;

	virtual void Do(std::shared_ptr<Player>& a_playerAction) const = 0;
};

} // namespace experis