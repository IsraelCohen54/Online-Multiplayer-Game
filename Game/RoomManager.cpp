#include "RoomManager.h"
#include "Player.h"
#include "Room.h"
#include "spdlog/spdlog.h" //logger
#include <random>

namespace experis
{

RoomManager::RoomManager()
: m_roomPlayers{}
, m_roomPlayerMutex{}
{
}

void RoomManager::RegisterPlayer(const RoomIndices& a_roomId, const std::shared_ptr<Player>& a_player) 
{
    a_player->NotifyRoomPlayers(a_roomId, a_player->GetName() + " has entered the room\n");
    {
        std::unique_lock<std::mutex> lockRoomManager(m_roomPlayerMutex);
        m_roomPlayers[a_roomId].insert(a_player); //[] better for insertion, no reason to worry using ".at(___)..."
    }
}

void RoomManager::UnregisterPlayer(const std::string& a_playerName)
{
    std::map<RoomIndices, std::unordered_set<std::shared_ptr<Player>>>::iterator roomsIt = m_roomPlayers.begin();
    for ( ; roomsIt != m_roomPlayers.end() ; ++roomsIt)
    {
        std::unordered_set<std::shared_ptr<Player>>::iterator playersIt = roomsIt->second.begin();
        for ( ; playersIt != roomsIt->second.end() ; ++playersIt)
        {
            if (playersIt->get()->GetName() == a_playerName)
            {
                std::string message = playersIt.operator*()->GetName() + " has left the game\n";
                std::pair<short, short> roomIndices = playersIt.operator*()->GetRoomIndices();
                {
                    std::unique_lock<std::mutex> lockRoomManager(m_roomPlayerMutex);
                    m_roomPlayers[roomsIt->first].erase(playersIt);
                }
                if (!roomsIt->second.empty()) //notify current room players that player has left the game
                {
                    roomsIt->second.begin()->get()->NotifyRoomPlayers(roomIndices, message);
                }
                return;
            }
        }
    }
}

void RoomManager::MovePlayerRoom(const RoomIndices& a_oldRoomIdx, const RoomIndices& a_newRoomIdx, const std::shared_ptr<Player>& a_player)
{
    {
        std::unique_lock<std::mutex> lockRoomManager(m_roomPlayerMutex);
        m_roomPlayers[a_newRoomIdx].insert(a_player); // "[] if doesn't exist - create room and insert
        m_roomPlayers[a_oldRoomIdx].erase(a_player);
    }
    return;
}

void RoomManager::NotifyCurrentRoomPlayers(const RoomIndices& a_roomId, const std::string& a_message)
{
    std::optional<std::map<RoomIndices, std::unordered_set<std::shared_ptr<Player>>>::const_iterator> roomIt = GetRelevantPlayersRoom(a_roomId);
    if (roomIt.has_value())
    {
        for (const std::shared_ptr<Player>& player : roomIt.value()->second)
        {
            player->ReceivedNotification(a_message);
        }
    }
    else
    {
        spdlog::debug("room {} was not found, you are the probably the first here\n", a_roomId.first, " ", a_roomId.second, " ", a_message);
    }
}

std::optional<std::shared_ptr<Player>> RoomManager::GetRandomPlayerInsideRoom(RoomIndices a_roomIndices, const std::shared_ptr<Player>& a_currentPlayer)
{
    std::optional<std::map<RoomIndices, std::unordered_set<std::shared_ptr<Player>>>::const_iterator> it 
        = GetRelevantPlayersRoom(a_roomIndices);
    assert(it.has_value()); // as at least current player inside this room
    if (it.value()->second.size() > 1)
    {
        std::random_device rd;
        size_t playerCount = it.value()->second.size();
        std::uniform_int_distribution<size_t> dist(0, playerCount - 1);
        size_t randomPlayerIndx = dist(rd);
        std::unordered_set<std::shared_ptr<Player>>::const_iterator playerIt = it.value()->second.begin();

        std::advance(playerIt, randomPlayerIndx);

        if (*playerIt == a_currentPlayer)
        {
            // If the selected player is the current player, increment the iterator to the next player
            ++playerIt;
            
            // Wrap around to the beginning if the iterator reaches the end
            if (playerIt == it.value()->second.end())
            {
                playerIt = it.value()->second.begin();
            } //else {}
        } // else {}

        return *playerIt;
    }
    else
    {
        return std::nullopt;
    }
}

auto RoomManager::GetRelevantPlayersRoom(const RoomIndices& a_roomId) ->
    std::optional<std::map<RoomIndices, std::unordered_set<std::shared_ptr<Player>>>::const_iterator>
{
    std::map<RoomIndices, std::unordered_set<std::shared_ptr<Player>>>::const_iterator roomIt 
        = m_roomPlayers.find(a_roomId);
    if (roomIt != m_roomPlayers.end())
    {
        return std::optional<std::map<RoomIndices, std::unordered_set<std::shared_ptr<Player>>>::const_iterator>(roomIt);
    } 
    else // no room found
    {
        return std::nullopt;
    }
}

std::mutex& RoomManager::GetMutex()
{
    return m_roomPlayerMutex;
}

} // namespace experis