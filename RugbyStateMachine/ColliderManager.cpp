#include "pch.h"
#include "Player.hpp"
#include "ColliderManager.hpp"

void ColliderManager::CheckCollision(Entity* entity1, Entity* entity2)
{
    if (!Utils::CheckCollision(entity1, entity2))
        return;

    float dt = GameManager::Get()->getDeltaTime();
    float speed2 = entity2->getSpeed();

    // Calculate the direction to repel each entity
    sf::Vector2f direction1 = Utils::Vector2Normalize(entity1->getPosition() - entity2->getPosition());

    // Repel the entities by an amount proportional to their speed
    entity1->setPosition(entity1->getPosition() + direction1 * speed2 * dt);
}


void ColliderManager::CheckDistanceCollision(Player* player1, Player* player2)
{
    if (player1->getTeam() == player2->getTeam() && Utils::FloatDistance(player1->getPosition(), player2->getPosition()) <= 10.f)
    {
        float avoidDistance = 10.f;

        if (player1->getPosition().y < player2->getPosition().y)
        {
            player1->setPosition(player1->getPosition() + sf::Vector2f(0, -avoidDistance));
            player2->setPosition(player2->getPosition() + sf::Vector2f(0, avoidDistance));
        }
        else
        {
            player1->setPosition(player1->getPosition() + sf::Vector2f(0, avoidDistance));
            player2->setPosition(player2->getPosition() + sf::Vector2f(0, -avoidDistance));
        }
    }
}