#include "LeftAction.h"
#include "Player.h"

namespace experis
{

void LeftAction::Do(std::shared_ptr<Player>& a_playerAction) const
{
	a_playerAction->TurnLeft();
}

} // experis namespace
