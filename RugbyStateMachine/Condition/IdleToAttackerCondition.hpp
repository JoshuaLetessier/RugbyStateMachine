#pragma once

class Condition;
class Player;

class IdleToAttackerCondition :
    public Condition
{
	float mDeltaTime = 0.f;
public:
	bool Test(Player* player) override;
};

