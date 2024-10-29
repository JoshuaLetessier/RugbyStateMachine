#pragma once

class Action;
class Ball;

class DefenserTakeBallAction : public Action
{
public:
    DefenserTakeBallAction();
	~DefenserTakeBallAction();

    void Start(Player* Player);
    void Update(Player* Player);
    void End(Player* Player);

private:
    Ball* mBall;
	Player* mBallKeeper;
};

