#pragma once

class Condition;
class Ball;
class Player;

class IdleToBallKeeperCondition :
    public Condition
{
	float mDeltaTime = 0.f;
public:
	bool Test(Player* player) override;
};

