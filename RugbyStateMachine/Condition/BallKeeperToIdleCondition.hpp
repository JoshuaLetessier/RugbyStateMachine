#pragma once

class Condition;
class Player;

class BallKeeperToIdleCondition : public Condition
{
public:
	bool Test(Player* player) override;
};

