#include "../pch.h"
#include "DefenserFollowBallAction.h"

#include "../Ball.hpp"
#include "../Player.hpp"
#include "../StateMachine/Action.hpp"
#include "../Utils.hpp"

void DefenserFollowBallAction::Start(Player* player)
{
	mBall = GameManager::GetBall();
	
	mPlayers = GameManager::GetPlayers();
}

void DefenserFollowBallAction::Update(Player* player)
{
	for (auto other : mPlayers)
	{
		ColliderManager::CheckCollision(player, other);
		ColliderManager::CheckDistanceCollision(player, other);
	}

	if (player->isOnLimit()) {
		player->goToPosition(mBall->getPosition());
	}
	else {
		sf::Vector2f direction(mBall->getPosition().x, player->getPosition().y);
		player->goToPosition(direction);
	}

}

void DefenserFollowBallAction::End(Player* player)
{
}
