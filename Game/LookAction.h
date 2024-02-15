#pragma once
#include <map>
#include <string>
#include <memory>
#include "Action.h"

namespace experis
{

class Room;

class Writer;

class LookAction : public Action
{
public:
	using Map = std::map<std::pair<short, short>, std::shared_ptr<Room>>;

	explicit LookAction() = delete;
	explicit LookAction(Writer& a_writer, Map& a_gameMap);
	LookAction(const LookAction& a_other) = delete;
	LookAction& operator=(const LookAction& a_other) = delete;
	virtual ~LookAction() override = default;

	virtual void Do(std::shared_ptr<Player>& a_player) const override;

private:
	Writer& m_writer;
	Map& m_gameMap;
};

} // namespace experis



