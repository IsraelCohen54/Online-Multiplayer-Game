#include "LookAction.h"
#include "Player.h"
#include "Room.h"
#include "Writer.h"

namespace experis
{

LookAction::LookAction(Writer& a_writer, Map& a_gameMap)
: m_writer{a_writer}
, m_gameMap{a_gameMap}
{
}

void LookAction::Do(std::shared_ptr<Player>& a_player) const
{
	std::string playerData{"\n> Player name: " + a_player->GetName() + ", current health: " + std::to_string(a_player->GetCurrentHealth()) + 
	", current attack: " + std::to_string(a_player->GetCurrentAttack()) + ".\n"};
	m_writer.Write("> " + m_gameMap[a_player->GetRoomIndices()].get()->GetRoomName() + playerData); //[] faster...
	
	//m_writer.Write(m_gameMap.at(gameMapRoomKey).get()->GetRoomName());
}

} // experis namespace
