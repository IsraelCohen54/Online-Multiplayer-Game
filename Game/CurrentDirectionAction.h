#pragma once

#include <array>
#include "Action.h"

namespace experis
{
class Writer;

class CurrentDirectionAction : public Action
{
public:
	explicit CurrentDirectionAction() = delete;
	explicit CurrentDirectionAction(Writer& a_writer);
	CurrentDirectionAction(const CurrentDirectionAction& a_other) = delete;
	CurrentDirectionAction& operator=(const CurrentDirectionAction& a_other) = delete;
	virtual ~CurrentDirectionAction() override = default;

	virtual void Do(std::shared_ptr<Player>& a_player) const override;

private:
	Writer& m_writer;
	std::array <std::string, 4> m_directionMessage;
};

} // namespace experis


