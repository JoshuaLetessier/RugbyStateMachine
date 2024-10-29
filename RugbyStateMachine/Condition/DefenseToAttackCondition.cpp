#include "../pch.h"
#include "../Condition/DefenseToAttackCondition.h"

#include "../Player.hpp"
#include "../Statemachine/Condition.hpp"

bool DefenseToAttackCondition::Test(Player* player)
{
	mEntities = GameManager::GetEntities();
	mPlayer = Utils::GetBallKeeper();

	if (mPlayer != nullptr && mPlayer->getTeam() == player->getTeam())
		return true;
    return false;
}
