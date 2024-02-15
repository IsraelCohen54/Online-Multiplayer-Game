#include "Room.h"

namespace experis
{

Room::Room(const RoomName& a_roomName, std::unique_ptr<Group> a_roomImage, const IsOpen a_northDoor,
	const IsOpen a_eastDoor, const IsOpen a_westDoor, const IsOpen a_southDoor, const RoomGrid a_roomGrid, std::optional<std::unique_ptr<TreasureBox>> a_treasureData)
: m_roomName{a_roomName}
, m_roomImage{std::move(a_roomImage)}
, m_north{a_northDoor}
, m_east{a_eastDoor}
, m_west{a_westDoor}
, m_south{a_southDoor}
, m_roomGrid{a_roomGrid}
, m_treasureData{std::move(a_treasureData)}
{
}

bool Room::IsNorthOpen() const
{
	return m_north;
}

bool Room::IsEastOpen() const
{
	return m_east;
}

bool Room::IsWestOpen() const
{
	return m_west;
}

bool Room::IsSouthOpen() const
{
	return m_south;
}

const Room::RoomGrid& Room::GetRoomLocation() const
{
	return m_roomGrid;
}

void Room::DrawGroup(ascii::ColoredCanvas& a_canvas) const
{
	this->m_roomImage->DrawGroup(a_canvas);
}

void Room::DrawTreasure(ascii::ColoredCanvas& a_canvas) const
{
	m_treasureData.value()->m_Paint.DrawGroup(a_canvas);
}

Room::RoomName Room::GetRoomName() const
{
	return m_roomName;
}

bool Room::SearchInsideRoom() const
{
	return (m_treasureData.has_value());
}

std::string Room::GetSearchResultMessage() const
{
	return m_treasureData.value()->m_message;
}

Room::Treasure Room::TakeTreasure() const
{
	return std::make_pair(m_treasureData.value()->m_health, m_treasureData.value()->m_attack);
}

} // experis namespace