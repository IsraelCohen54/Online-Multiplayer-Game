#pragma once

#include "Action.h"

namespace experis
{

class RightAction : public Action
{
public:
	explicit RightAction() = default;
	RightAction(const RightAction& a_other) = delete;
	RightAction& operator=(const RightAction& a_other) = delete;
	virtual ~RightAction() override = default; //good practice IMO, so if change would occur, a reminder...

	virtual void Do(std::shared_ptr<Player>& a_playerAction) const override;
};

} // namespace experis

