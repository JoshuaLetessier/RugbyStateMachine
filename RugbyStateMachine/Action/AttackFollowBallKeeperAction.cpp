#include "../pch.h"
#include "AttackFollowBallKeeperAction.h"

#include "../Player.hpp"
#include "../StateMachine/Action.hpp"
#include "../Utils.hpp"


AttackFollowBallKeeperAction::AttackFollowBallKeeperAction()
{
}

AttackFollowBallKeeperAction::~AttackFollowBallKeeperAction()
{
}

void AttackFollowBallKeeperAction::Start(Player* player)
{
	mPlayers = GameManager::GetPlayers();
	mBallKeeper = Utils::GetBallKeeper();
}

void AttackFollowBallKeeperAction::Update(Player* player)
{
	if (mBallKeeper == nullptr)
		return;

	for (auto other : mPlayers)
	{
		ColliderManager::CheckCollision(player, other);
		ColliderManager::CheckDistanceCollision(player, other);
	}

	if (player->isOnLimit()) {
		sf::Vector2f direction(mBallKeeper->getPosition().x - 30.f, player->getPosition().y);
		player->goToPosition(direction);
	}
	else {
		sf::Vector2f direction(mBallKeeper->getPosition().x, player->getPosition().y);
		player->goToPosition(direction);
	}
}

void AttackFollowBallKeeperAction::End(Player* player)
{
}
