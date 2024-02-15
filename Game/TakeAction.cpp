#include "TakeAction.h"
#include "Player.h"

namespace experis
{

void TakeAction::Do(std::shared_ptr<Player>& a_playerAction) const
{
	a_playerAction->TakeTreasures();
}

} // experis namespace

