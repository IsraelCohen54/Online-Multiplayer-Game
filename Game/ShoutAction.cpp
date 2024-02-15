#include "ShoutAction.h"
#include "Player.h"
#include "Room.h"
#include "Writer.h"
#include "Reader.h"

namespace experis
{

ShoutAction::ShoutAction(Reader& a_reader, Map& a_gameMap)
: m_reader{a_reader}
, m_gameMap{a_gameMap}
{
}

RoomIndices ShoutAction::CreateMapKeyFrom2Num(const short a_num, const short a_num2) const
{
	return RoomIndices{a_num, a_num2};
}

void ShoutAction::Do(std::shared_ptr<Player>& a_playerAction) const
{
	std::string playerShouting;
	m_reader.ReadLine(playerShouting);
	auto [x, y] = a_playerAction->GetRoomIndices();
	a_playerAction->NotifyRoomPlayers(a_playerAction->GetRoomIndices(),playerShouting);
	
	//static constexpr unsigned short NORTHEN_ROOM = 1 + x; //tried to go without magic number... const wansn't good here..
	
	Map::const_iterator itForNorthRoomCheck = m_gameMap.find(CreateMapKeyFrom2Num(1 + x, y));
	if (itForNorthRoomCheck != m_gameMap.end())
	{
		a_playerAction->NotifyRoomPlayers(CreateMapKeyFrom2Num(1 + x, y),playerShouting);
	} //else {}
	Map::const_iterator itForEastRoomCheck = m_gameMap.find(CreateMapKeyFrom2Num(x, 1 + y));
	if (itForEastRoomCheck != m_gameMap.end())
	{
		a_playerAction->NotifyRoomPlayers(CreateMapKeyFrom2Num(x, 1 + y),playerShouting);
	} //else {}
	Map::const_iterator itForSouthRoomCheck = m_gameMap.find(CreateMapKeyFrom2Num(x, y - 1));
	if (itForSouthRoomCheck != m_gameMap.end())
	{
		a_playerAction->NotifyRoomPlayers(CreateMapKeyFrom2Num(x, y - 1),playerShouting);
	} //else {}
	Map::const_iterator itWest = m_gameMap.find(CreateMapKeyFrom2Num(x - 1, y ));
	if (itWest != m_gameMap.end())
	{
		a_playerAction->NotifyRoomPlayers(CreateMapKeyFrom2Num(x - 1, y),playerShouting);
	} //else {}
}

} // experis namespace
