#include "TalkAction.h"
#include "Player.h"
#include "Reader.h"

namespace experis
{
TalkAction::TalkAction(Reader& a_reader)
: m_reader{a_reader}
{
}

void TalkAction::Do(std::shared_ptr<Player>& a_playerAction) const
{
	std::string userTalking;
	m_reader.ReadLine(userTalking);

	a_playerAction->NotifyRoomPlayersWithMessage(userTalking);
}

} // experis namespace
