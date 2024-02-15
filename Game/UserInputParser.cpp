#include "UserInputParser.h"
#include "LeftAction.h"
#include "RightAction.h"
#include "HelpAction.h"
#include "Writer.h"
#include "CurrentDirectionAction.h"
#include "WalkAction.h"
#include "LookAction.h"
#include "TalkAction.h"
#include "Reader.h"
#include "ShoutAction.h"
#include "AttackAction.h"
#include "SearchAction.h"
#include "TakeAction.h"

namespace experis
{

UserInputParser::UserInputParser(Writer& a_writer, Map& a_gameMap, Reader& a_reader)
{
	m_name2Action.insert(std::make_pair("left", std::make_unique<LeftAction>()));
	m_name2Action.insert(std::make_pair("right", std::make_unique<RightAction>()));
	m_name2Action.insert(std::make_pair("direction", std::make_unique<CurrentDirectionAction>(a_writer)));
	m_name2Action.insert(std::make_pair("help", std::make_unique<HelpAction>(a_writer, m_name2Action)));
	m_name2Action.insert(std::make_pair("walk", std::make_shared<WalkAction>(a_writer, a_gameMap)));
	m_name2Action.insert(std::make_pair("look", std::make_shared<LookAction>(a_writer, a_gameMap)));
	m_name2Action.insert(std::make_pair("talk", std::make_shared<TalkAction>( a_reader)));
	m_name2Action.insert(std::make_pair("shout", std::make_shared<ShoutAction>(a_reader, a_gameMap)));
	m_name2Action.insert(std::make_pair("attack", std::make_unique<AttackAction>()));
	m_name2Action.insert(std::make_pair("search", std::make_unique<SearchAction>()));
	m_name2Action.insert(std::make_pair("take", std::make_unique<TakeAction>()));
}

bool UserInputParser::IsValid(const std::string& a_txt) const
{
	if (m_name2Action.find(a_txt) != m_name2Action.end() || a_txt == "exit")
	{
		return true;
    }
	else
	{	 
        return false;
    }
	return false;
}

Action& UserInputParser::Parse(const std::string& a_txt) const
{
	std::unordered_map<std::string, std::shared_ptr<Action>>::const_iterator it =  m_name2Action.find(a_txt);
	
	assert(it != m_name2Action.end());
	return *it->second;
}

} // UserInputParser