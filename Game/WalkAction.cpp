#include <cassert>
#include <array>
#include "WalkAction.h"
#include "Player.h"
#include "Writer.h"


namespace experis
{

WalkAction::WalkAction(Writer& a_writer, Map& a_gameMap)
: m_writer{a_writer}
, m_gameMap{a_gameMap}
{
}

// <summary>
/// 1. get current x,y room location
/// 2. get player facing location
/// 3. add + 1 to relevant room index by player facing direction ~~~ (0, 0) is down left grid ~~~
/// 4. get key map from 2 (convert to string)
/// 4. check if room exist, if so - change player room, else, write to player he can't move there.
/// </summary>
/// <param name="a_playerAction"></param>
//
void WalkAction::Do(std::shared_ptr<Player>& a_playerAction) const
{
	static constexpr short NORTH = 0;
	static constexpr short EAST = 1;
	static constexpr short SOUTH = 2;
	static constexpr short WEST = 3;
	
	auto [x, y] = a_playerAction->GetRoomIndices();
	WalkAction::RoomKey currentMapRoomKey = this->CreateMapKeyFrom2Num(x,y);
	experis::Player::Direction currentDir = a_playerAction->GetDirection();
	std::string direction{};
	
	// Todo LUT!!!
	/*std::array<std::pair<std::string, std::pair<short, short>>, 4> tryWalkForward
	{std::pair<std::string, std::pair<short, short>>{std::string{"north"}, std::pair<short, short>(0, 1)},
	std::pair<std::string, std::pair<short, short>>{std::string{"east"}, std::pair<short, short>(1, 0)},
	std::pair<std::string, std::pair<short, short>>{std::string{"south"}, std::pair<short, short>(0, -1)},
		std::pair<std::string, std::pair<short, short>>{std::string{"west"}, std::pair<short, short>(-1, 0)}
	};
	auto[direction, std::pair<short, short>(addXVal, addYVal)] = tryWalkForward[1];
	*/
	if (short(currentDir) == NORTH)
	{
		direction = std::string{"north"};
		++y;
	}
	else if (short(currentDir) == EAST)
	{
		direction = std::string{"east"};
		++x;
	}
	else if (short(currentDir) == SOUTH)
	{
		direction = std::string{"south"};
		--y;
	}
	else if (short(currentDir) == WEST)
	{
		direction = std::string{"west"};
		--x;
	}
	else 
	{
		assert(!"wrong direction");
	}
	RoomKey nextMapRoomKey = this->CreateMapKeyFrom2Num(x,y);
	bool it = m_gameMap.contains(this->CreateMapKeyFrom2Num(x,y));
	if (it)
	{
		//optionally do notify inside room manager, same IMO 
		a_playerAction->NotifyRoomPlayers(nextMapRoomKey, "> " + a_playerAction->GetName() + std::string{" has entered the room.\n"});
		a_playerAction->UpdatePlayerRoomRegistration(currentMapRoomKey, nextMapRoomKey, a_playerAction);
		a_playerAction->ChangeRoom(m_gameMap[nextMapRoomKey], currentMapRoomKey, nextMapRoomKey, currentDir);
		a_playerAction->NotifyRoomPlayers(currentMapRoomKey, "> " + a_playerAction->GetName() + std::string{" has left room.\n"});
	}
	else
	{
		m_writer.Write("> You need a pickaxe to walk there. No door exists at " + direction + "\n");
		a_playerAction->ChangeHealth(-1);
		int curHealth = a_playerAction->GetCurrentHealth();
		if (curHealth)
		{	
			m_writer.Write("> Next time, don't bash your head into a wall, you have lost one health! current health: " + std::to_string(curHealth));
		} //else died...
	}
}

WalkAction::RoomKey WalkAction::CreateMapKeyFrom2Num(const short a_num, const short a_num2) const
{
	return RoomKey{a_num, a_num2};
}

} // experis namespace
