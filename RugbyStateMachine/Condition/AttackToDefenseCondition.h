#pragma once

class Condition;

class AttackToDefenseCondition :
    public Condition
{
public:
	bool Test(Player* player) override;
private:
	std::vector<Entity*> mEntities;
	Player* mPlayer;
};

