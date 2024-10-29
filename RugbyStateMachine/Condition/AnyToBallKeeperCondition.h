#pragma once

class Condition;

class AnyToBallKeeperCondition : public Condition
{
public:
	AnyToBallKeeperCondition();
	~AnyToBallKeeperCondition();

	bool Test(Player* player) override;

private:
	bool mFirstTime = true;
};

