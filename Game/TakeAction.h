#pragma once

#include "Action.h"

namespace experis
{

class TakeAction : public Action
{
public:
	explicit TakeAction() = default;
	TakeAction(const TakeAction& a_other) = delete;
	TakeAction& operator=(const TakeAction& a_other) = delete;
	virtual ~TakeAction() override = default; //good practice IMO, reminder for if would be changed etc

	virtual void Do(std::shared_ptr<Player>& a_playerAction) const override;
};

} // namespace experis

