#pragma once

class Action;
class Ball;
class Player;

class BallKeeperPassAction :
    public Action
{
	Ball* mBall = nullptr;
	std::vector<Player*> mAllyPlayer;
	std::vector<Player*> mEnemyPlayer;

	sf::Clock clock;
	float mCurrentTime;

public:
	void Start(Player* player) override;
	void Update(Player* player) override;
	void End(Player* player) override;
	void setTeams(Context::Team team);
	Player* findClosestEnemy(Player* player) const;
	Player* findClosestAllyBehind(Player* player) const;
};

