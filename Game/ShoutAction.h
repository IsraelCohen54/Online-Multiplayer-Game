#pragma once

#include <map>
#include <string>
#include "Action.h"

namespace experis
{

class Room;
using RoomIndices = std::pair<short, short>;
using Map = std::map<RoomIndices, std::shared_ptr<Room>>;

class Reader;
class Player;

class ShoutAction : public Action
{
public:
	explicit ShoutAction() = delete;
	explicit ShoutAction(Reader& a_reader, Map& a_gameMap);
	ShoutAction(const ShoutAction& a_other) = delete;
	ShoutAction& operator=(const ShoutAction& a_other) = delete;
	virtual ~ShoutAction() override = default;

	virtual void Do(std::shared_ptr<Player>& a_playerAction) const override;

private:
	Reader& m_reader;
	Map& m_gameMap;

	RoomIndices CreateMapKeyFrom2Num(const short a_num, const short a_num2) const;
};

} // namespace experis
