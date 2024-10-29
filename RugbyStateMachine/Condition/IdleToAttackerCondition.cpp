#include "../pch.h"
#include "../Player.hpp"
#include "../Ball.hpp"
#include "../Condition/IdleToAttackerCondition.hpp"

bool IdleToAttackerCondition::Test(Player* player)
{
	if (player->isStunned())
	{
		return false;
	}

	Ball* ball = GameManager::GetBall();
	Player* ballKeeper = ball->getPlayer();

	if (ballKeeper == nullptr)
	{
		mDeltaTime = 0.f;
		return true;
	}

	if (ballKeeper != nullptr && ballKeeper->getTeam() == player->getTeam())
	{
		mDeltaTime = 0.f;
		return true;
	}

	return false;
}