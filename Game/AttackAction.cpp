#include "AttackAction.h"

#include "Player.h"

namespace experis
{

void AttackAction::Do(std::shared_ptr<Player>& a_playerAction) const
{
	a_playerAction->AttackPlayer(a_playerAction);
}

} // experis namespace
