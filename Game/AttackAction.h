#pragma once

#include "Action.h"

namespace experis
{

class AttackAction : public Action
{
public:
	explicit AttackAction() = default;
	AttackAction(const AttackAction& a_other) = delete;
	AttackAction& operator=(const AttackAction& a_other) = delete;
	virtual ~AttackAction() override = default; //good practice IMO, reminder for if would be changed etc

	virtual void Do(std::shared_ptr<Player>& a_playerAction) const override;
};

} // namespace experis



