#pragma once

#include <string>
#include <memory>
#include <vector>
#include "ascii/colored_canvas.hpp"

namespace experis
{

class Room;
class Writer;
class RoomManager;

class Player
{
	using Name = std::string;
	using ChangeLife = short;
	using ChangeAttackPower = short;
	using Life = unsigned short;
	using Attack = unsigned short;
	using RoomIdices = std::pair<short, short>;
	using SearchedRoom = std::vector<std::pair<std::pair<short, short>, bool>>;

public:
	explicit Player() = delete;
	explicit Player(const Name& a_playerName, std::shared_ptr<Room> a_currentRoom,
		std::shared_ptr<Writer>& a_writer, ascii::ColoredCanvas& a_canvas, RoomManager& a_roomManager);
	Player(const Player& a_other); // make_shared into roomsManager DB
	Player& operator=(const Player& a_other) = delete;
	~Player() = default;

	enum class Direction
	{
		NORTH,
		EAST,
		SOUTH,
		WEST,
		COUNT_DIRECTIONS
	};

	void TurnRight();
	void TurnLeft();
	void DrawRoom(ascii::ColoredCanvas& a_canvas);
	void ChangeRoom(std::shared_ptr<Room> a_newRoom, const RoomIdices& a_mapRoomKey, const RoomIdices& nextMapRoomKe, const Player::Direction a_direction);
	Direction GetDirection();
	RoomIdices GetRoomIndices();
	const Name& GetName() const;
	Life GetCurrentHealth() const;
	Attack GetCurrentAttack() const;
	void ChangeHealth(const ChangeLife a_changeLife);
	void ChangeAttack(const ChangeAttackPower a_changeAttack);
	void AttackPlayer(std::shared_ptr<Player>& a_player) const;
	void SearchRoom();
	void TakeTreasures();

	void NotifyRoomPlayers(const RoomIdices& a_roomIdx, const std::string& a_message);
	void ReceivedNotification(const std::string& a_notification);
	void UpdatePlayerRoomRegistration(const RoomIdices& a_currentMapRoomKey, const RoomIdices& a_nextMapRoomKey, std::shared_ptr<Player>& a_thisPlayer);
	void NotifyRoomPlayersWithMessage(const std::string& a_message);

private:
	Player::Direction m_currentDirectionOnCanvas;
	Name m_playerName;
	std::shared_ptr<Room> m_currentRoom;
	std::shared_ptr<Writer>& m_writer;
	ascii::ColoredCanvas& m_canvas;
	Life m_life;
	Attack m_attack;
	RoomManager& m_roomManager;
	SearchedRoom m_searchedRoom;

	static constexpr bool TREASURE_TAKEN_ALREADY = true;
	void PlayerDeath() const;
};

} // namespace experis