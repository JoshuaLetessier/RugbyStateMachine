#include "../pch.h"
#include "DefenserTakeBallAction.h"

#include "../StateMachine/Action.hpp"
#include "../Player.hpp"
#include "../Ball.hpp"
#include "../Utils.hpp"

DefenserTakeBallAction::DefenserTakeBallAction()
{
}

DefenserTakeBallAction::~DefenserTakeBallAction()
{
}

void DefenserTakeBallAction::Start(Player* Player)
{
	//Get the ball
	mBall = GameManager::GetBall();
	mBallKeeper = mBall->getPlayer();

}

void DefenserTakeBallAction::Update(Player* player)
{
	mBallKeeper = mBall->getPlayer();
	// Test if the ballKeeper invincibility is active
	if (mBallKeeper && mBallKeeper->getIsInvisible())
	{
		return;
	}

	//Test if the player has a collision with the ball
	if (mBall && Utils::CheckCollision(player, mBall))
	{
		mBall->setPlayer(player);
		mBall->setPosition(player->getPosition());
	}
	else if (mBallKeeper && Utils::CheckCollision(player, mBallKeeper))
	{
		mBall->setPlayer(player);
		mBall->setPosition(player->getPosition());
	}
}

void DefenserTakeBallAction::End(Player* Player)
{
}
