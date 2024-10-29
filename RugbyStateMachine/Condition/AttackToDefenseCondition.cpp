#include "../pch.h"
#include "AttackToDefenseCondition.h"

#include "../Player.hpp"
#include "../Utils.hpp"

bool AttackToDefenseCondition::Test(Player* player)
{
	mEntities = GameManager::GetEntities();
	mPlayer = Utils::GetBallKeeper();
	if (mPlayer == nullptr)
		return true;
	else if (mPlayer != nullptr && mPlayer->getTeam() != player->getTeam())
		return true;
	return false;
}
