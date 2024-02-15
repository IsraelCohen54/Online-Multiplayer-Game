#include <chrono>
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <thread>
#include <windows.h>
#include <iostream>
#include <conio.h>
#include <array>

#include "Group.h"
#include "Player.h"
#include "RoomManager.h"
#include "Room.h"
#include "Writer.h" //compiler needs to know funcionality, so class declaration not enough, check if 'reference' has correct functionality

namespace experis
{
namespace detail //means, DO NOT CHANGE, especially do not change array ordering
{
static constexpr std::array<char, size_t(Player::Direction::COUNT_DIRECTIONS)> directionSymbols = {
    'A', '>', 'V', '<'
};

} //detail namespace

Player::Player(const Name& a_playerName, std::shared_ptr<Room> a_currentRoom,
    std::shared_ptr<Writer>& a_writer, ascii::ColoredCanvas& a_canvas, RoomManager& a_roomManager)
: m_currentDirectionOnCanvas{Player::Direction::NORTH}
, m_playerName{a_playerName}
, m_currentRoom{a_currentRoom}
, m_writer{a_writer}
, m_canvas{a_canvas}
, m_roomManager{a_roomManager}
, m_searchedRoom{}
, m_life{2}
, m_attack{1}
{
}

Player::Player(const Player& a_other)
: m_currentDirectionOnCanvas{a_other.m_currentDirectionOnCanvas}
, m_playerName{a_other.m_playerName}
, m_currentRoom{a_other.m_currentRoom}
, m_writer{a_other.m_writer}
, m_canvas{a_other.m_canvas}
, m_roomManager{a_other.m_roomManager}
, m_life{a_other.m_life}
, m_attack{a_other.m_attack}
, m_searchedRoom{a_other.m_searchedRoom}
{
}

Player::Direction Player::GetDirection()
{
	return m_currentDirectionOnCanvas;
}

// <summary>
/// The std::modulo() function will return a value between 0 and Player::Direction::COUNT_DIRECTIONS - 1.
/// So, if m_currentDirectionOnCanvas is -1, the std::modulo() function will return 3.
/// </summary>
void Player::TurnLeft()
{
    m_currentDirectionOnCanvas = static_cast<Direction>((static_cast<int>(m_currentDirectionOnCanvas) - 1 +
		static_cast<int>(Direction::COUNT_DIRECTIONS)) % static_cast<int>(Direction::COUNT_DIRECTIONS));
    m_canvas(15, 15) = detail::directionSymbols[size_t(m_currentDirectionOnCanvas)];
}

void Player::TurnRight()
{
	m_currentDirectionOnCanvas = Player::Direction((static_cast<int>(m_currentDirectionOnCanvas) + 1) %
        static_cast<int>(Player::Direction::COUNT_DIRECTIONS));
	m_canvas(15, 15) = detail::directionSymbols[size_t(m_currentDirectionOnCanvas)];
}

const Player::Name& Player::GetName() const
{
    return m_playerName;
}

Player::Life Player::GetCurrentHealth() const
{
    return m_life;
}


Player::Attack Player::GetCurrentAttack() const
{
    return m_attack;
}

void Player::ChangeHealth(const ChangeLife a_changeLife)
{
    m_life += a_changeLife;
    if (m_life <= 0)
    {
        this->m_roomManager.UnregisterPlayer(GetName());
        PlayerDeath();
    } //else {}
}

void Player::ChangeAttack(const ChangeAttackPower a_changeAttack)
{
    m_attack += a_changeAttack;
    m_writer->Write("Your current attack is: " + std::to_string(m_attack) + "\n");
}

void Player::AttackPlayer(std::shared_ptr<Player>& a_player) const
{
    std::optional<std::shared_ptr<Player>> playerToAttack = m_roomManager.GetRandomPlayerInsideRoom(m_currentRoom->GetRoomLocation(), a_player);
    if (playerToAttack.has_value())
    {
        playerToAttack.value()->m_writer->Write("You have been attacked by " + m_playerName +
            " for " + std::to_string(m_attack) + " damage, bad luck. Your heath currently is: " + std::to_string(playerToAttack.value()->m_life - 1) + "\n");
        playerToAttack.value()->ChangeHealth(- m_attack);
    }
    else
    {
        m_writer->Write("You are alone here, no one to attack\n");
    }
}

void Player::SearchRoom()
{
    if (!m_currentRoom->SearchInsideRoom())
    {
        m_writer->Write("> You have found...! you have found...!!! only yourself here, and maybe some dust, too bad.\n");
    } 
    else 
    {
        m_writer->Write("> Wow! A treasure Box! It contains: " + m_currentRoom->GetSearchResultMessage() + "\n");
        m_searchedRoom.push_back(std::make_pair(GetRoomIndices(), false));
        m_currentRoom.get()->DrawTreasure(m_canvas);
    }
}

void Player::TakeTreasures()
{
    //Todo change to unordered set with appropriate hash for key as pair... currently vector as "no time.." and without hash it's not supported
    auto indices = this->GetRoomIndices();
    std::vector<std::pair<std::pair<short, short>, bool>>::iterator iter = std::find_if(m_searchedRoom.begin(), m_searchedRoom.end(),
        [&](const auto& element)
        {
            return element.first == indices;
        });
    if (iter != m_searchedRoom.end())
    {
        if (iter->second == !TREASURE_TAKEN_ALREADY)
        {
            std::pair<short, short> treasure = m_currentRoom->TakeTreasure();
            if (treasure.first)
            {
                this->ChangeHealth(treasure.first);
                m_writer->Write("> Current life is: " + std::to_string(m_life) + ".\n");
            }
            if (treasure.second)
            {
                this->ChangeAttack(treasure.second);
            }
            iter->second = TREASURE_TAKEN_ALREADY;
        }
        else
        {
            m_writer->Write("> The treasure box is empty, and it would stay so even if you try to take from it again.\n");
        }
    }
    else
    {
        m_writer->Write("> There is nothing to take here.\n");
    }
}

void digitalRain(Writer& output);
void Player::PlayerDeath() const
{
    m_writer.get()->Write("> Your health currently is 0, apparently, you have died.");
    std::this_thread::sleep_for(std::chrono::seconds(5));
    
     // Initialize the raindrops
    std::string raindrops(10, '*');

    //digitalRain(*m_writer.get());
}

void digitalRain(Writer& output)
{
    const int screenWidth = 80;
    const int screenHeight = 25;
    
    const int numColumns = screenWidth;

    srand(static_cast<unsigned int>(time(nullptr)));

    struct Column
    {
        int y;
        char symbol;
        int length;
        int speed;
    };

    Column columns[numColumns]{};

    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hOut, &cursorInfo);

    auto clearScreen = [&]()
    {
        COORD topLeft = {0, 0};
        HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
        CONSOLE_SCREEN_BUFFER_INFO screen;
        DWORD written;

        GetConsoleScreenBufferInfo(console, &screen);
        FillConsoleOutputCharacterA(
            console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
        );
        FillConsoleOutputAttribute(
            console, FOREGROUND_GREEN, screen.dwSize.X * screen.dwSize.Y, topLeft, &written
        );
        SetConsoleCursorPosition(console, topLeft);
    };

    auto drawColumns = [&](const Column columns[], int numColumns)
    {
        for (int i = 0; i < numColumns; ++i)
        {
            const Column& column = columns[i];
            if (column.y >= 0 && column.y < screenHeight)
            {
                COORD pos = {short(i), short(column.y)};
                SetConsoleCursorPosition(hOut, pos);
                SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
                std::string str(1, column.symbol);
                output.Write(str);
            }
        }
    };

    auto updateColumns = [&](Column columns[], int numColumns)
{
    for (int i = 0; i < numColumns; ++i)
    {
        Column& column = columns[i];
        if (column.y >= screenHeight)
        {
            column.y = -1;
            column.symbol = rand() % 94 + 33; // ASCII characters from '!' to '~'
            column.speed = rand() % 3 + 1;
        }
        else if (column.y >= 0)
        {
            // Generate a new character below the existing character
            columns[i].y = column.y - 1;
            columns[i].symbol = rand() % 94 + 33; // ASCII characters from '!' to '~'
            columns[i].speed = rand() % 3 + 1;
        }

        column.y += column.speed;
    }
};

    for (int i = 0; i < numColumns; ++i)
    {
        columns[i].y = rand() % 2 - screenHeight;
        columns[i].symbol = rand() % 94 + 33; // ASCII characters from '!' to '~'
        columns[i].length = rand() % (screenHeight - 1) + 1;
        columns[i].speed = rand() % 3 + 1;
    }
    while (true != 0)
    {
        clearScreen();
        updateColumns(columns, numColumns);
        drawColumns(columns, numColumns);
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

void Player::DrawRoom(ascii::ColoredCanvas& a_canvas)
{
	m_currentRoom.get()->DrawGroup(a_canvas);
	std::stringstream paint{};
	a_canvas.Print(paint, ascii::ColoredCanvas::OutputPosition::CURRENT_LINE);
	m_writer->Write(paint.str());
}

Player::RoomIdices Player::GetRoomIndices()
{
	return m_currentRoom.get()->GetRoomLocation();
}

void Player::UpdatePlayerRoomRegistration(const RoomIdices& a_currentMapRoomKey, const RoomIdices& a_nextMapRoomKey, std::shared_ptr<Player>& a_thisPlayer)
{
    this->m_roomManager.MovePlayerRoom(a_currentMapRoomKey, a_nextMapRoomKey, a_thisPlayer);
}

void Player::ChangeRoom(std::shared_ptr<Room> a_newRoom, const RoomIdices& a_currentMapRoomKey, const RoomIdices& a_nextMapRoomKey, const Player::Direction a_currentDir)
{
    m_currentRoom = a_newRoom;
    m_canvas.Clear();
    m_canvas(15, 15) = detail::directionSymbols[size_t(a_currentDir)];
}

void Player::NotifyRoomPlayers(const RoomIdices& a_roomIdx, const std::string& a_message)
{
    m_roomManager.NotifyCurrentRoomPlayers(a_roomIdx, a_message);
}

void Player::NotifyRoomPlayersWithMessage(const std::string& a_message)
{
    NotifyRoomPlayers(GetRoomIndices(), a_message);
}

void Player::ReceivedNotification(const std::string& a_notification)
{
    m_writer->Write("> " + a_notification + "\n");
}

} // namespace experis