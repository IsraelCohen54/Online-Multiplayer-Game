#include "HelpAction.h"
#include "UserInputParser.h"
#include "Writer.h"

namespace experis
{

HelpAction::HelpAction(Writer& a_writer, std::unordered_map<std::string, std::shared_ptr<Action>>& a_userCommands)
: m_writer{a_writer}
, m_commandsData{a_userCommands}
{
}

void HelpAction::Do(std::shared_ptr<Player>& a_player) const
{
	m_writer.Write("\n> The commands are:");
	std::unordered_map<std::string, std::shared_ptr<Action>>::const_iterator it =  m_commandsData.begin();
	m_writer.Write(" " + it->first);
	for ( ++it ; it != m_commandsData.end(); ++it)
	{
		m_writer.Write(", " + it->first);
	}
	m_writer.Write(", exit.");
}

} // experis namespace
