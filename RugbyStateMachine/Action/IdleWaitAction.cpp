#include "../pch.h"
#include "../Player.hpp"
#include "../Action/IdleWaitAction.hpp"

void IdleWaitAction::Start(Player* player)
{
	for (auto other : GameManager::Get()->GetPlayers())
	{
		ColliderManager::CheckCollision(player, other);
	}
	player->goToPosition(player->getPosition());
}

void IdleWaitAction::Update(Player* player)
{
	player->setPosition(player->getPosition());
}

void IdleWaitAction::End(Player* player)
{
}