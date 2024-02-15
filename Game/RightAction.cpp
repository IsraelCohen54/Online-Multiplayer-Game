#include "RightAction.h"
#include "Player.h"

namespace experis
{

void RightAction::Do(std::shared_ptr<Player>& a_playerAction) const
{
	a_playerAction->TurnRight();
}

} // experis namespace
