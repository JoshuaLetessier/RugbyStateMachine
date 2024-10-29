#pragma once

class Action;
class Ball;
class Player;

class DefenserFollowBallAction :
    public Action
{
public:
	void Start(Player* player) override;
	void Update(Player* player) override;
	void End(Player* player) override;

private:
	Ball* mBall = nullptr;
	std::vector<Player*> mPlayers;
};

