#pragma once

class Condition;
class Player;

class DefenseToAttackCondition : public Condition
{
public:
	bool Test(Player* player) override;

private:
	std::vector<Entity*> mEntities;
	Player* mPlayer;
};

