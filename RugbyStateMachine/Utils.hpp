#pragma once

class Entity;
class Ball;
class Player;

namespace Utils
{
	sf::Vector2f Vector2Normalize(const sf::Vector2f& vector);
	sf::Vector2f Vector2Direction(const sf::Vector2f& vector1, const sf::Vector2f& vector2);
	sf::Vector2f Vector2Multiply(const sf::Vector2f& vector1, const sf::Vector2f& vector2);
	float GetDeltaTime();
	float FloatDistance(const sf::Vector2f& vector1, const sf::Vector2f& vector2);
	bool IsPlayerBehind(const Context::Team playerColor, const sf::Vector2f& playerVector, const sf::Vector2f& allyVector);
	float GetDeltaTime();
	Ball* GetBall(std::vector<Entity*> mEntities);
	Player* GetBallKeeper();
	std::vector<Player*> GetRedPlayers(std::vector<Entity*> mEntities);
	std::vector<Player*> GetGreenPlayers(std::vector<Entity*> mEntities);
	bool RangeBetweenPlayers(Player* player1, Player* player2);
	std::optional<sf::Vector2f> ComputeAvoidanceVector(Player* player, const std::vector<Entity*>& entities);
	bool CheckCollision(Entity* entity1, Entity* entity2);
}