#pragma once

class Action;


class AttackFollowBallKeeperAction :
    public Action
{
public:
	AttackFollowBallKeeperAction();
	virtual ~AttackFollowBallKeeperAction();

	void Start(Player* player) override;
	void Update(Player* player) override;
	void End(Player* player) override;

private:
	std::vector<Player*> mPlayers;
	Player* mBallKeeper;
};

