#include "../pch.h"
#include "../Ball.hpp"
#include "../Player.hpp"
#include "../Condition/IdleToDefenserCondition.hpp"

bool IdleToDefenserCondition::Test(Player* player)
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

	if (ballKeeper != nullptr && ballKeeper->getTeam() != player->getTeam())
	{
		mDeltaTime = 0.f;
		return true;
	}

	return false;
}