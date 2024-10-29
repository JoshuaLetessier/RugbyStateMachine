#include "../pch.h"
#include "../Ball.hpp"
#include "../Player.hpp"
#include "../Condition/IdleToBallKeeperCondition.hpp"

bool IdleToBallKeeperCondition::Test(Player *player)
{
	if (player->isStunned())
	{
		return false;
	}

	Ball *ball = GameManager::GetBall();
	Player *ballKeeper = ball->getPlayer();

	bool isBallInsidePlayer = ball->getShape().getGlobalBounds().intersects(player->getShape().getGlobalBounds());

	if (ballKeeper == nullptr && isBallInsidePlayer)
	{
		mDeltaTime = 0.f;
		return true;
	}

	return false;
}