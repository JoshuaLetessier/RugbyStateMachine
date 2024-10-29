#include "../pch.h"
#include "AnyToBallKeeperCondition.h"

#include "../Player.hpp"
#include "../Ball.hpp"
#include "../StateMachine/Condition.hpp"
#include "../Utils.hpp"

AnyToBallKeeperCondition::AnyToBallKeeperCondition()
{
}

AnyToBallKeeperCondition::~AnyToBallKeeperCondition()
{
}

bool AnyToBallKeeperCondition::Test(Player* player)
{
	//Get the ball
	Ball* ball = Utils::GetBall(GameManager::GetEntities());

	if (!mFirstTime && ball->getPlayer() == player)
		return false;
	else if (ball->getPlayer() == player)
	{
		mFirstTime = false;
	}

	if (ball->getPlayer() == player)
	{
		mFirstTime = true;
		return true;
	}
	else
		return false;

	return false;
}
