#include "../pch.h"
#include "../Ball.hpp"
#include "../Player.hpp"
#include "../Condition/BallKeeperToIdleCondition.hpp"

bool BallKeeperToIdleCondition::Test(Player* player)
{
	Player* ballKeeper = GameManager::GetBall()->getPlayer();

	if (ballKeeper == nullptr || ballKeeper->getTeam() != player->getTeam())
		return true;

	return false;
}