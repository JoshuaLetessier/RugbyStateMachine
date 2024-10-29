#pragma once

class Action;
class Player;

class BallKeeperTryoutAction
	: public Action
{
public:
	void Start(Player* player) override;
	void Update(Player* player) override;
	void End(Player* player) override;
};

