#pragma once
#include <string>
#include "Group.h"

namespace experis
{

class TreasureBox
{
	friend class Room;

	using Health = short;
	using Attack = short;
	using TreasureMessage = std::string;
	using TreasurePaint = Group;

public:
	explicit TreasureBox() = delete;
	explicit TreasureBox(const Health a_health, const Attack a_attack, const TreasureMessage& a_message);
	TreasureBox(const TreasureBox& a_other) = delete;
	TreasureBox& operator=(const TreasureBox& a_other) = delete;
	~TreasureBox() = default;

private:
	const Health m_health;
	const Attack m_attack;
	const TreasureMessage m_message;
	TreasurePaint m_Paint; //not const for adding paint to game paining, argument there isn't const...
};

} // experis namespace