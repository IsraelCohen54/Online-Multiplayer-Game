#pragma once

#include <map>
#include <string>
#include <memory>
#include "Action.h"

namespace experis
{
class Room;
class Writer;

class WalkAction : public Action
{
using RoomKey = std::pair<short, short>;
using Map = std::map<RoomKey, std::shared_ptr<Room>>;
	
public:
	explicit WalkAction() = delete;
	explicit WalkAction(Writer& a_writer, Map& a_gameMap);
	WalkAction(const WalkAction& a_other) = delete;
	WalkAction& operator=(const WalkAction& a_other) = delete;
	virtual ~WalkAction() override = default;

	virtual void Do(std::shared_ptr<Player>& a_playerAction) const override;

private:
	Writer& m_writer;
	Map& m_gameMap;

	RoomKey CreateMapKeyFrom2Num(const short a_num, const short a_num2) const;
};

} // namespace experis