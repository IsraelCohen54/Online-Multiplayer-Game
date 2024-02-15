#pragma once

#include <string>
#include <memory>
#include <unordered_map>
#include <map>
#include <cassert>
#include "Action.h"
#include "HelpAction.h"

namespace experis
{
class Writer;
class Reader;
class Room;

class UserInputParser
{
	friend class HelpAction;
	using RoomKey = std::pair<short, short>;
	using Map = std::map<RoomKey, std::shared_ptr<Room>>;
	using Name2Action = std::unordered_map<std::string, std::shared_ptr<Action>>;

public:
	explicit UserInputParser() = delete;
	explicit UserInputParser(Writer& a_writer, Map& a_gameMap, Reader& a_reader);
	UserInputParser(const UserInputParser& a_other) = delete;
	UserInputParser& operator=(const UserInputParser& a_other) = delete;
	~UserInputParser() = default;

	bool IsValid(const std::string& a_txt) const;
	Action& Parse(const std::string& a_txt) const;

private:
	Name2Action m_name2Action;
};

} // namespace experis