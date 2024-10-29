#pragma once

class Entity;
class Player;

class ColliderManager
{
public:
	static void CheckCollision(Entity* entity1, Entity* entity2);
	static void CheckDistanceCollision(Player* entity1, Player* entity2);
};

