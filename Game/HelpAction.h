#pragma once

#include <unordered_map>
#include <memory>
#include <string>
#include "Action.h"


namespace experis
{
class Writer;

class HelpAction: public Action
{

public:
	explicit HelpAction() = delete;
	explicit HelpAction(Writer& a_writer, std::unordered_map<std::string, std::shared_ptr<Action>>& a_userCommands);
	HelpAction(const HelpAction& a_other) = delete;
	HelpAction& operator=(const HelpAction& a_other) = delete;
	virtual ~HelpAction() override = default;

	virtual void Do(std::shared_ptr<Player>& a_player) const override;

private:
	Writer& m_writer;
	std::unordered_map<std::string, std::shared_ptr<Action>>& m_commandsData;
};

} // namespace experis

