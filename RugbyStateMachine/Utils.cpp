#include "pch.h"
#include "Utils.hpp"

#include "Ball.hpp"
#include "Player.hpp"

namespace Utils
{

	sf::Vector2f Vector2Normalize(const sf::Vector2f& vector)
	{
		float magnitude = std::sqrt(vector.x * vector.x + vector.y * vector.y);

		if (magnitude == 0) {
			return { 0, 0 };
		}

		sf::Vector2f normalized = { vector.x / magnitude, vector.y / magnitude };

		return normalized;
	}

	sf::Vector2f Vector2Direction(const sf::Vector2f& vector1, const sf::Vector2f& vector2)
	{
		sf::Vector2f direction = { vector2.x - vector1.x, vector2.y - vector1.y };

		return Vector2Normalize(direction);
	}

	sf::Vector2f Vector2Multiply(const sf::Vector2f& vector1, const sf::Vector2f& vector2)
	{
		return { vector1.x * vector2.x, vector1.y * vector2.y };
	}

    float GetDeltaTime()
    {
        return 0.016f;
    }

	Ball* GetBall(std::vector<Entity*> mEntities)
	{
		for (Entity* entity : mEntities)
		{
			Ball* tBall = dynamic_cast<Ball*>(entity);
			if (tBall)
			{
				return tBall;
			}
		}
	}

	Player* GetBallKeeper()
	{
		Ball* ball = GameManager::GetBall();
		return ball ? ball->getPlayer() : nullptr;
	}

	std::vector<Player*> GetRedPlayers(std::vector<Entity*> mEntities)
	{
		std::vector<Player*> redPlayers;
		for (Entity* entity : mEntities)
		{
			Player* player = dynamic_cast<Player*>(entity);
			if (player && player->getTeam() == Context::Team::RED)
			{
				redPlayers.push_back(player);
			}
		}
		return redPlayers;
	}

	std::vector<Player*> GetGreenPlayers(std::vector<Entity*> mEntities)
	{
		std::vector<Player*> bluePlayers;
		for (Entity* entity : mEntities)
		{
			Player* player = dynamic_cast<Player*>(entity);
			if (player && player->getTeam() == Context::Team::GREEN)
			{
				bluePlayers.push_back(player);
			}
		}
		return bluePlayers;
	}

	bool RangeBetweenPlayers(Player* player1, Player* player2)
	{
		const float minRange = 100.0f;
		sf::Vector2f pos1 = player1->getPosition();
		sf::Vector2f pos2 = player2->getPosition();

		float distanceSquared = std::pow(pos2.x - pos1.x, 2) + std::pow(pos2.y - pos1.y, 2);

		return distanceSquared > (minRange * minRange);
	}

	std::optional<sf::Vector2f> ComputeAvoidanceVector(Player* player, const std::vector<Entity*>& entities)
	{
		std::vector<Player*> teamPlayers = (player->getTeam() == Context::Team::RED) ?
			Utils::GetRedPlayers(entities) :
			Utils::GetGreenPlayers(entities);

		sf::Vector2f avoidanceVector(0.0f, 0.0f);
		int closeTeammates = 0;

		for (Player* teammate : teamPlayers)
		{
			if (player != teammate && !Utils::RangeBetweenPlayers(player, teammate))
			{
				sf::Vector2f diff = player->getPosition() - teammate->getPosition();
				sf::Vector2f normalizedDiff = Utils::Vector2Normalize(diff);
				avoidanceVector += normalizedDiff;
				closeTeammates++;
			}
		}

		// Si on a des coéquipiers trop proches, on retourne le vecteur d'évitement
		if (closeTeammates > 0)
		{
			avoidanceVector /= static_cast<float>(closeTeammates);
			return avoidanceVector * 10.0f; // Ajuste `10.0f` pour un écart souhaité
		}

		// Pas de coéquipiers trop proches
		return std::nullopt;
	}

	float FloatDistance(const sf::Vector2f& vector1, const sf::Vector2f& vector2)
	{
		return std::sqrt(std::pow(vector2.x - vector1.x, 2) + std::pow(vector2.y - vector1.y, 2));
	}

	bool IsPlayerBehind(const Context::Team playerColor, const sf::Vector2f& playerVector, const sf::Vector2f& otherVector)
	{
		if (playerColor == Context::Team::GREEN)
		{
			return playerVector.x > otherVector.x;
		}
		else
		{
			return playerVector.x < otherVector.x;
		}
	}

	bool CheckCollision(Entity* entity1, Entity* entity2)
	{
		if (entity1->getShape().getGlobalBounds().intersects(entity2->getShape().getGlobalBounds()))
		{
			return true;
		}
		return false;
	}
}
