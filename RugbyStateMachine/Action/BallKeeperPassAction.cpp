#include "../pch.h"
#include "../Ball.hpp"
#include "../Player.hpp"
#include "../Action/BallKeeperPassAction.hpp"

void BallKeeperPassAction::Start(Player *player)
{
	// Get the current time with clock
	player->setInvisible(true);
	player->setSpeed(75);
	mCurrentTime = clock.getElapsedTime().asSeconds();

	mBall = GameManager::GetBall();

	setTeams(player->getTeam());
}

void BallKeeperPassAction::Update(Player *player)
{
	float elapsedTime = clock.getElapsedTime().asSeconds();

	// Vérification de l'invisibilité
	if (elapsedTime >= mCurrentTime + 3)
	{
		player->setInvisible(false);
		player->setSpeed(50);
		clock.restart();
	}

	// Exécuter le passage si le joueur est visible
	if (!player->getIsInvisible())
	{
		Player* closestEnemy = findClosestEnemy(player);
		Player* closestAllyBehind = findClosestAllyBehind(player);

		// Passer la balle si un ennemi proche et un allié derrière sont détectés
		if (Utils::FloatDistance(player->getPosition(), closestEnemy->getPosition()) <= DISTANCE_TO_PASS && closestAllyBehind != nullptr)
		{
			mBall->goToPosition(closestAllyBehind->getPosition());
			mBall->setPlayer(nullptr);
			player->setStunned(GameManager::Get()->getDeltaTime() + 1.0f);
		}

#ifdef _DEBUG
		if (closestAllyBehind)
			closestAllyBehind->getShape().setOutlineColor(sf::Color::Transparent);
#endif
	}
}

void BallKeeperPassAction::End(Player *player)
{
}

void BallKeeperPassAction::setTeams(Context::Team team)
{
	if (team == Context::Team::GREEN)
	{
		mAllyPlayer = GameManager::GetPlayersByTeam(Context::Team::GREEN);
		mEnemyPlayer = GameManager::GetPlayersByTeam(Context::Team::RED);
	}
	else
	{
		mAllyPlayer = GameManager::GetPlayersByTeam(Context::Team::RED);
		mEnemyPlayer = GameManager::GetPlayersByTeam(Context::Team::GREEN);
	}
}

Player* BallKeeperPassAction::findClosestEnemy(Player* player) const
{
	Player* closestEnemy = mEnemyPlayer[0];
	for (Player* enemy : mEnemyPlayer)
	{
		if (Utils::FloatDistance(player->getPosition(), enemy->getPosition()) < Utils::FloatDistance(player->getPosition(), closestEnemy->getPosition()))
		{
			closestEnemy = enemy;
		}
	}
	return closestEnemy;
}

Player* BallKeeperPassAction::findClosestAllyBehind(Player* player) const
{
	Player* closestAlly = nullptr;
	for (Player* ally : mAllyPlayer)
	{
		if (Utils::IsPlayerBehind(player->getTeam(), player->getPosition(), ally->getPosition()) && ally->getState() != Context::State::IDLE && ally->getState() != Context::State::DEFEND)
		{
			if (!closestAlly || Utils::FloatDistance(player->getPosition(), ally->getPosition()) < Utils::FloatDistance(player->getPosition(), closestAlly->getPosition()))
			{
				closestAlly = ally;
			}
		}
	}
	return closestAlly;
}
