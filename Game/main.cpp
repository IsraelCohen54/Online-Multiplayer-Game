#include <iostream>
#include <cassert>
#include <list>
#include <chrono>
#include <thread>
#include <unordered_map>
#include <typeinfo> // in retrospect, it wasn't really needed
#include <memory>  //unique & shared ptr
#include <string>
#include <mutex>

#include "Reader.h"
#include "Writer.h"
#include "RoomManager.h"
#include "Point.h"
#include "ShapeFactory.h"
#include "UserInputParser.h"
#include "Player.h"
#include "LeftAction.h"
#include "RightAction.h"
#include "Room.h"
#include "SimpleNetMT.h"   //Telnet
#include "UrlPathReader.h" //Telnet
#include "spdlog/spdlog.h" //logger
#include "Circle.h"
#include "TreasureBox.h"

namespace experis
{
using namespace std::chrono_literals;

static constexpr unsigned short MAX_PORT_NUM = 65535; //Fun fact, it is the max num for unsigned short!
static constexpr unsigned short MIN_PORT_NUM = 1024;

using RoomAxis = std::pair<short, short>;
using ChoseColor = ascii::ColoredCanvas;
using Connection = simplenet::SimpleNetMT::Connection;
using ClosedConnection = simplenet::SimpleNetMT::ConnectionClosed;

namespace detail
{

class AfterActionNotification
{
public:
    explicit AfterActionNotification(Writer& a_writer)
    : m_writer{a_writer}
    {
        std::pair<size_t, std::string> actionLeft(std::make_pair(typeid(experis::LeftAction&).hash_code(), std::string{"> You have turned left.\n"}));
        m_commands.insert(actionLeft);

        std::pair<size_t, std::string> actionRight(std::make_pair(typeid(experis::RightAction&).hash_code(), std::string{"> You have turned right.\n"}));
        m_commands.insert(actionRight);
    }
    AfterActionNotification(const AfterActionNotification& a_other) = delete;
    AfterActionNotification& operator=(const AfterActionNotification& a_other) = delete;
    ~AfterActionNotification() = default;

    void NotifyActionDone(const size_t& a_actionType, UserInputParser& a_commands, std::shared_ptr<Player>& a_player)
    {
        std::unordered_map<size_t, std::string>::const_iterator it = m_commands.find(a_actionType);
	    if (it != m_commands.end())
        {
            m_writer.Write(it->second);
            a_commands.Parse(std::string{"direction"}).Do(a_player);
        } // else {}
    }

private:
    std::unordered_map<size_t, std::string> m_commands;
    Writer& m_writer;
};

} // namespace detail

void PlayGame(std::shared_ptr<Writer> a_writer, const std::unique_ptr<Reader> a_reader, Map& a_gameMap, RoomManager& a_roomManager, std::string& a_unregisterPlayerAtEndByName)
{
    // opening messages:
    a_writer->Write("> What is your name?\n");
    std::string playerName{};
    a_reader->ReadLine(playerName);
    a_unregisterPlayerAtEndByName = playerName;
    a_writer->Write("> Welcome To the game " + playerName + "! you are facing North.\n");
    a_writer->Write("> To know the game commands, write help.\n");
    
    ascii::ColoredCanvas gameCanvas{99, 27};
    gameCanvas(15, 15) = 'A';
    std::shared_ptr<Player> playerPlaying = std::make_shared<Player>(playerName, a_gameMap.at({1, 1}), a_writer, gameCanvas, a_roomManager);

    a_roomManager.RegisterPlayer({1, 1}, playerPlaying);

    //Starting the game:
    while(playerPlaying->GetCurrentHealth() > 0)
    {
        playerPlaying->DrawRoom(gameCanvas);
        std::string untrust_userInput{};
        UserInputParser userInputParser{*a_writer, a_gameMap, *a_reader};
        do
        {
            a_reader->ReadLine(untrust_userInput);
        } while (!userInputParser.IsValid(untrust_userInput));
        
        const std::string& userInput = untrust_userInput;
        if (userInput == "exit")
        {
            a_writer->Write("> You have exited the game. Goodbye\n");
            a_roomManager.UnregisterPlayer(playerName);
            break;
        } // else{}
        Action& action = userInputParser.Parse(userInput);
        action.Do(playerPlaying);

        const std::type_info& actionType = typeid(action); // (In retrospect, I could have used the command string instead of typeid to identify the command)
        detail::AfterActionNotification detailedCommandResult{*a_writer};
        detailedCommandResult.NotifyActionDone(actionType.hash_code(), userInputParser, playerPlaying);
    }
}

void PlayWithAttachedReaderWriterToConnection(Map& a_gameMap, RoomManager& a_roomManager, std::shared_ptr<Connection>a_connection)
{
    std::string unregisterPlayerAtEnd{};
    try
    {
        std::unique_ptr<Reader> readTelnet{std::make_unique<TelnetReader>(a_connection)};
        std::shared_ptr<Writer> writeTelnet{std::make_shared<TelnetWriter>(a_connection)};
        writeTelnet->Write("Welcome to Telnet! and, (drums.....!)\n\n");
        std::this_thread::sleep_for(std::chrono::seconds(1));

        PlayGame(std::move(writeTelnet), std::move(readTelnet)
            , std::ref(a_gameMap), std::ref(a_roomManager), unregisterPlayerAtEnd);
    }
    catch (const ClosedConnection&)
    {
        a_roomManager.UnregisterPlayer(unregisterPlayerAtEnd); // roomManager lock is inside UnregisterPlayer func
        std::cerr << "CLOSED\n";
    }
}

// <summary>
/// using telnet with: set localecho (to see writing inside telnet)
/// open 127.0.0.1 4010 (127.0.0.1 - current computer, else ping(Ipv4) needed, 4010 - port number defined)
/// </summary>
void PlayViaTelnet(unsigned short a_portNum, Map& a_gameMap, RoomManager& a_roomManager)
{
    using namespace std::chrono_literals;
    simplenet::SimpleNetMT net{a_portNum};
	while (true)
	{
        //PlayWithAttachedReaderWriterToConnection(a_gameMap, std::move(connection), std::ref(a_roomManager));

        std::shared_ptr<Connection> connection = std::make_shared<Connection> (net.WaitForConnection());
        std::thread check(&PlayWithAttachedReaderWriterToConnection, std::ref(a_gameMap), std::ref(a_roomManager), std::move(connection));
        check.detach();
	}
    assert(!"outside while loop at telnet");
}

bool IsPortNumeric(const std::string& a_str)
{
    for (const char c : a_str)
    {
        if (c < '0' || c > '9')
        {
            return false;
        }
    }
    return true;
}

//<summary>
/// Gets arguments from main arguments,
///     and by argument type, launch the game via Telnet or Console or both.
/// 
/// Args:
///   argc: The number of arguments.
///   argv: An array of pointers to the arguments.
/// 
/// Run the game with program arguments of:
/// <console>                        || start the game via console.
/// <number> (=> Telnet port number) || start the game via telnet.
/// <number> <Console>               || start the game via console + telnet.
/// </summary>
void LaunchGameViaProgramArguments(int argc, char** argv, Map& a_gameMap, RoomManager& a_roomManager)
{
    if (argc == 2 && !IsPortNumeric(argv[1]))
    {
        std::unique_ptr<Writer> writeStream = std::make_unique<OstreamWriter>(std::cout);
        std::unique_ptr<Reader> readStream = std::make_unique<IstreamReader>(std::cin);
        std::string nonRelevantForOneUserOnly("");
        PlayGame(std::move(writeStream), std::move(readStream), a_gameMap, a_roomManager, nonRelevantForOneUserOnly);
    }
    else if (argc == 2 && IsPortNumeric(argv[1]))
    {
        assert(MIN_PORT_NUM < std::stoull(argv[1]) && std::stoull(argv[1]) < MAX_PORT_NUM);
        PlayViaTelnet(std::stoi(argv[1]), std::ref(a_gameMap), std::ref(a_roomManager));
    }
    else if (argc == 3 && strcmp(argv[2], "console") == 0 && IsPortNumeric(argv[1]))
    {
        assert(MIN_PORT_NUM < std::stoull(argv[1]) && std::stoull(argv[1]) < MAX_PORT_NUM);
        
        std::thread th_telnet(&PlayViaTelnet, std::stoi(argv[1]), std::ref(a_gameMap), std::ref(a_roomManager));

        std::unique_ptr<Writer> writeStream = std::make_unique<OstreamWriter>(std::cout);
        std::unique_ptr<Reader> readStream = std::make_unique<IstreamReader>(std::cin);
        std::string nonRelevantForOneUserOnlyInConsoleAfterTelnetClosedViaJoin("");

        PlayGame(std::move(writeStream), std::move(readStream), a_gameMap, a_roomManager, nonRelevantForOneUserOnlyInConsoleAfterTelnetClosedViaJoin);
        
        th_telnet.join();
    }
    else
    {
        spdlog::error("Wrong arguments number or type to program, argc number: {}, and should have been in range of 1 to 3\n", argc);
        assert(!"Wrong arguments number or type to program");
    }
}

// <summary>
/// creating walls, doors, lights as one group - room
/// </summary>
void CreateRoomPaint(Group& a_group, const bool a_northOpen, const bool a_eastOpen, const bool a_southOpen, const bool a_westOpen, ChoseColor::Color a_colour)
{   // Todo (the same without the ifs  below)
    
    static constexpr unsigned short ROOM_WIDTH = 25;
    static constexpr unsigned short ROOM_HEIGHT = 25;
    static constexpr unsigned short LIGHT_RADIUS = 0;
    static constexpr unsigned short LIGHT_Y = 8;
    static constexpr unsigned short LIGHT_X = 8;
    
    // Adding lights to the candle corners
    a_group.Add<Circle, Point, double>(Point{LIGHT_X, LIGHT_Y -1}, LIGHT_RADIUS, ChoseColor::BLACK, ChoseColor::YELLOW, '.');
    a_group.Add<Circle, Point, double>(Point{ROOM_WIDTH - 3, LIGHT_Y -1}, LIGHT_RADIUS, ChoseColor::BLACK, ChoseColor::YELLOW, '.');
    a_group.Add<Circle, Point, double>(Point{LIGHT_X, ROOM_HEIGHT - 4}, LIGHT_RADIUS, ChoseColor::BLACK, ChoseColor::YELLOW, '.');
    a_group.Add<Circle, Point, double>(Point{ROOM_WIDTH - 3, ROOM_HEIGHT - 4}, LIGHT_RADIUS, ChoseColor::BLACK, ChoseColor::YELLOW, '.');

    // Room walls:
    a_group.Add<Rectangle, Point, Point>(Point{ROOM_WIDTH, ROOM_HEIGHT}, Point{5, 5}, a_colour, ChoseColor::BLACK, 'H');
    
    // Adding door by demand to room:
    if (a_northOpen)
    {
        a_group.Add<Line, Point, Point>(Point{18, 5}, Point{12, 5},
            ChoseColor::BLACK, ChoseColor::BLACK, '_');
    }
    if (a_eastOpen)
    {
        a_group.Add<Line, Point, Point>(Point{ROOM_WIDTH, 17},
            Point{ROOM_WIDTH, 13}, ChoseColor::BLACK, ChoseColor::BLACK, '|');
    }
    if (a_southOpen)
    {
        a_group.Add<Line, Point, Point>(Point{18, ROOM_HEIGHT}
        , Point{12, ROOM_HEIGHT}, ChoseColor::BLACK, ChoseColor::BLACK, '_');
    }
    if (a_westOpen)
    {
        a_group.Add<Line, Point, Point>(Point{5, 17}, Point{5, 13}
        , ChoseColor::BLACK, ChoseColor::BLACK, '|');
    }

    // Adding candles for the lights above
    short lightToBottom = ROOM_HEIGHT - 3;
    a_group.Add<Line, Point, Point>(Point{LIGHT_X, LIGHT_Y}, Point{LIGHT_X, LIGHT_Y + 1}, ChoseColor::WHITE, ChoseColor::WHITE, '|');
    a_group.Add<Line, Point, Point>(Point{LIGHT_X, lightToBottom}, Point{LIGHT_X, lightToBottom + 1}, ChoseColor::WHITE, ChoseColor::WHITE, '_');
    a_group.Add<Line, Point, Point>(Point{ROOM_WIDTH - 3, LIGHT_Y}, Point{ROOM_WIDTH - 3, LIGHT_Y + 1}, ChoseColor::WHITE, ChoseColor::WHITE, '|');
    a_group.Add<Line, Point, Point>(Point{ROOM_WIDTH - 3, lightToBottom}, Point{ROOM_WIDTH - 3, lightToBottom + 1}, ChoseColor::WHITE, ChoseColor::WHITE, '|');

    // adding lantern "o" inside:
    //a_group.Add<Circle, Point, double>(Point{LIGHT_X, LIGHT_Y}, 0, ChoseColor::WHITE, ChoseColor::YELLOW, '0');
    //a_group.Add<Circle, Point, double>(Point{LIGHT_X, lightToBottom}, 0, ChoseColor::WHITE, ChoseColor::YELLOW, '0');
    //a_group.Add<Circle, Point, double>(Point{ROOM_WIDTH - 3, LIGHT_Y}, 0, ChoseColor::WHITE, ChoseColor::YELLOW, '0');
    //a_group.Add<Circle, Point, double>(Point{ROOM_WIDTH - 3, lightToBottom}, 0, ChoseColor::WHITE, ChoseColor::YELLOW, '0');

    // To save & load image to and from a file works well if needed:
    /*SavePainting(std::string{"D:\\visual_studio_projs\\Experis_algo\\Shapes\\beginRoom.txt"}, room);
    experis::ShapeFactory a_shapeFactory{};
    Group newHobitHome2 = LoadPainting(std::string{"D:\\visual_studio_projs\\Experis_algo\\Shapes\\beginRoom.txt"}, a_shapeFactory);
    ascii::ColoredCanvas gameCanvas{99, 27};
    newHobitHome2.DrawGroup(gameCanvas);
    gameCanvas.Print(std::cout);
    exit(0);*/
}

void CreateGameRooms(Map& a_gameMap)
{
    static constexpr bool NORTH_OPEN = true;
    static constexpr bool EAST_OPEN = true;
    static constexpr bool SOUTH_OPEN = true;
    static constexpr bool WEST_OPEN = true;
    static constexpr bool treasureBox = true;
    using TreasureBoxData = std::pair<std::string, short>;
    
    std::unique_ptr<Group> beginRoomImg = std::make_unique<Group>();
    CreateRoomPaint(*beginRoomImg.get() ,NORTH_OPEN, !EAST_OPEN, !SOUTH_OPEN, !WEST_OPEN, ChoseColor::WHITE);
    std::shared_ptr<Room> beginRoom = std::make_shared<Room>(std::string{"Begin Room"}, std::move(beginRoomImg),
        NORTH_OPEN, !EAST_OPEN, !SOUTH_OPEN, !WEST_OPEN, std::pair<short, short>(1, 1), std::nullopt);
    
    std::unique_ptr<Group> secRoomImage = std::make_unique<Group>();
    CreateRoomPaint(*secRoomImage.get() ,NORTH_OPEN, EAST_OPEN, SOUTH_OPEN, !WEST_OPEN, ChoseColor::YELLOW);
    std::shared_ptr<Room> secondRoom = std::make_shared<Room>(std::string{"Second Room"}, std::move(secRoomImage),
        NORTH_OPEN, EAST_OPEN, SOUTH_OPEN, !WEST_OPEN, std::pair<short, short>(1, 2), std::make_unique<TreasureBox>(3, 0, "Health potion! "));

    std::unique_ptr<Group> thirdRoomImage = std::make_unique<Group>();
    CreateRoomPaint(*thirdRoomImage.get() ,!NORTH_OPEN, !EAST_OPEN, SOUTH_OPEN, !WEST_OPEN, ChoseColor::GREEN);
    std::shared_ptr<Room> thirdRoom = std::make_shared<Room>(std::string{"Third Room"}, std::move(thirdRoomImage),
        !NORTH_OPEN, !EAST_OPEN, SOUTH_OPEN, !WEST_OPEN, std::pair<short, short>(1, 3), std::make_unique<TreasureBox>(0, 3, "Attack potion! "));

    std::unique_ptr<Group> forthRoomImage = std::make_unique<Group>();
    CreateRoomPaint(*forthRoomImage.get() ,!NORTH_OPEN, !EAST_OPEN, !SOUTH_OPEN, WEST_OPEN, ChoseColor::BLUE);
    std::shared_ptr<Room> forthRoom = std::make_shared<Room>(std::string{"Forth Room"}, std::move(forthRoomImage),
        !NORTH_OPEN, !EAST_OPEN, !SOUTH_OPEN, WEST_OPEN, std::pair<short, short>(2, 2), std::make_unique<TreasureBox>(5, 5, "Health and attack potion! "));

    a_gameMap.emplace(std::make_pair(RoomAxis{1, 1},std::shared_ptr<Room>(beginRoom)));
    a_gameMap.emplace(std::make_pair(RoomAxis{1, 2},std::shared_ptr<Room>(secondRoom)));
    a_gameMap.emplace(std::make_pair(RoomAxis{1, 3},std::shared_ptr<Room>(thirdRoom)));
    a_gameMap.emplace(std::make_pair(RoomAxis{2, 2},std::shared_ptr<Room>(forthRoom)));
}

} //expleris namespace

int main(int argc, char** argv)
{    
    using namespace experis;
    
    experis::Map gameMap{};
    CreateGameRooms(gameMap);

    RoomManager roomManager{};
    LaunchGameViaProgramArguments(argc, argv, gameMap, roomManager);
}