#include <string>
#include <cassert>
#include "CurrentDirectionAction.h"
#include "Player.h"
#include "Writer.h"

namespace experis
{
CurrentDirectionAction::CurrentDirectionAction(Writer& a_writer)
: m_writer{a_writer}
, m_directionMessage{
	"> You are facing North.\n"
	,"> You are facing East.\n"
	,"> You are facing South.\n"
	,"> You are facing West.\n"}
{
}

void CurrentDirectionAction::Do(std::shared_ptr<Player>& a_player) const
{
	short direction = static_cast<int>(a_player->GetDirection());
	assert(direction >= 0 && direction < 4);
	m_writer.Write(m_directionMessage[direction]);
	/*switch (direction)
	{
	case(0):
	{
		m_writer.Write("> You are facing North\n");
		break;
	}
	case(1):
	{
		m_writer.Write("> You are facing East\n");
		break;
	}
	case(2):
	{
		m_writer.Write("> You are facing South\n");
		break;
	}
	case(3):
	{
		m_writer.Write("> You are facing West\n");
		break;
	}
	default:
		break;
	}*/
}

} // experis namespace
