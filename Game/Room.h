#pragma once

#include <memory>
#include <optional>
#include <string>
#include "Group.h"
#include "TreasureBox.h"
//#include "ascii/colored_canvas.hpp"

class colored_canvas;

namespace experis
{

class Room
{

public:
	using IsOpen = bool;
	using RoomGrid = std::pair<short, short>;
	using RoomName = std::string;
	using Treasure = std::pair<short, short>;

	explicit Room() = delete;
	explicit Room(const RoomName& a_roomName, std::unique_ptr<Group>(a_roomImage), const IsOpen a_northDoor,
		const IsOpen a_eastDoor, const IsOpen a_westDoor, const IsOpen a_southDoor, const RoomGrid a_roomGrid, std::optional<std::unique_ptr<TreasureBox>> a_treasureData);
	Room(const Room& a_other) = default; // for creating game map
	Room& operator=(const Room& a_other) = delete;
	~Room() = default;

	bool IsNorthOpen() const;
	bool IsEastOpen() const;
	bool IsWestOpen() const;
	bool IsSouthOpen() const;
	const RoomGrid& GetRoomLocation() const;
	void DrawGroup(ascii::ColoredCanvas& a_canvas) const;
	RoomName GetRoomName() const;
	void DrawTreasure(ascii::ColoredCanvas& a_canvas) const;
	bool SearchInsideRoom() const;
	std::string GetSearchResultMessage() const;
	Treasure TakeTreasure() const;

private:
	const RoomName m_roomName;
	std::unique_ptr<Group> m_roomImage;
	const IsOpen m_north;
	const IsOpen m_east;
	const IsOpen m_west;
	const IsOpen m_south;
	const RoomGrid m_roomGrid;
	std::optional<std::unique_ptr<TreasureBox>> m_treasureData;
};

} // namespace experis