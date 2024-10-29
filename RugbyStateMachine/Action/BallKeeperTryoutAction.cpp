#include "../pch.h"
#include "../Player.hpp"
#include "../Action/BallKeeperTryoutAction.hpp"

void BallKeeperTryoutAction::Start(Player* player)
{
}

void BallKeeperTryoutAction::Update(Player* player)
{
	if (player->getTeam() == Context::Team::GREEN)
	{
		if(player->getPosition().x > RED_TEAM_GOAL)
		{ 
			GameManager::setScoreGreen(1);
			GameManager::setWin();
		}
	}
	else
	{
		if (player->getPosition().x < GREEN_TEAM_GOAL)
		{
			GameManager::setScoreRed(1);
			GameManager::setWin();
		}
	}
}

void BallKeeperTryoutAction::End(Player* player)
{
}