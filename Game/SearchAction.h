#pragma once

#include "Action.h"

namespace experis
{

class SearchAction : public Action
{
public:
	explicit SearchAction() = default;
	SearchAction(const SearchAction& a_other) = delete;
	SearchAction& operator=(const SearchAction& a_other) = delete;
	virtual ~SearchAction() override = default; //good practice IMO, reminder for if would be changed etc

	virtual void Do(std::shared_ptr<Player>& a_playerAction) const override;
};

} // namespace experis
