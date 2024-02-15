#include "SearchAction.h"

#include "Player.h"

namespace experis
{

void SearchAction::Do(std::shared_ptr<Player>& a_playerAction) const
{
	a_playerAction->SearchRoom();
}

} // experis namespace

