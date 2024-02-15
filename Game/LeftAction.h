#pragma once

#include "Action.h"

namespace experis
{

class LeftAction : public Action
{
public:
	explicit LeftAction() = default;
	LeftAction(const LeftAction& a_other) = delete;
	LeftAction& operator=(const LeftAction& a_other) = delete;
	virtual ~LeftAction() override = default; //good practice IMO, reminder for if would be changed etc

	virtual void Do(std::shared_ptr<Player>& a_playerAction) const override;
};

} // namespace experis

