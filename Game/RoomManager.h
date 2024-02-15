#pragma once

#include <memory>
#include <map>
#include <unordered_set> //used for storing vals/keys only, good of second val for map if per key many are relevant...
#include <string>
#include <optional>
#include <mutex>

namespace experis
{
using RoomIndices = std::pair<short, short>;

class Room;
using Map = std::map<RoomIndices, std::shared_ptr<Room>>;
    
class Player;

class RoomManager
{
public:
    using RoomIndices = std::pair<short, short>;

    explicit RoomManager();
    RoomManager(const RoomManager& a_other) = delete;
    RoomManager& operator=(const RoomManager& a_other) = delete;
    ~RoomManager() = default;

    void RegisterPlayer(const RoomIndices& a_roomId, const std::shared_ptr<Player>& a_player); //const & => read only about Player
    void UnregisterPlayer(const std::string& a_playerName);
    void MovePlayerRoom(const RoomIndices& oldRoomKey, const RoomIndices& newRoomKey, const std::shared_ptr<Player>& a_player);
    auto GetRelevantPlayersRoom(const RoomIndices& a_roomId)
        -> std::optional<std::map<RoomIndices, std::unordered_set<std::shared_ptr<Player>>>::const_iterator>;

    std::optional<std::shared_ptr<Player>> GetRandomPlayerInsideRoom(RoomIndices a_roomIndices, const std::shared_ptr<Player>& a_currentPlayer);
    void NotifyCurrentRoomPlayers(const RoomIndices& a_roomId, const std::string& a_message);
    std::mutex& GetMutex();

private:
    std::map<RoomIndices, std::unordered_set<std::shared_ptr<Player>>> m_roomPlayers;
    std::mutex m_roomPlayerMutex;
};

} // experis namespace