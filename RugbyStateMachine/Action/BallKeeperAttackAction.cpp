#include "../pch.h"
#include "../Ball.hpp"
#include "../Player.hpp"
#include "../Action/BallKeeperAttackAction.hpp"

void BallKeeperAttackAction::Start(Player* player)
{
    mBall = GameManager::GetBall();
    mPlayers = GameManager::GetPlayers();
}

void BallKeeperAttackAction::Update(Player* player)
{
    for (Player* other : mPlayers)
    {
        ColliderManager::CheckCollision(player, other);
        ColliderManager::CheckDistanceCollision(player, other);
    }

    player->goToPosition(getGoalPosition(player->getTeam(), player->getPosition().y));

    if (mBall)
        mBall->setPosition(player->getPosition());
}

void BallKeeperAttackAction::End(Player* player)
{
}

sf::Vector2f BallKeeperAttackAction::getGoalPosition(Context::Team team, float y) const
{
    return (team == Context::Team::GREEN) ? sf::Vector2f(RED_TEAM_GOAL, y) : sf::Vector2f(GREEN_TEAM_GOAL, y);
}