#pragma once

class Action;
class Ball;
class Player;

class BallKeeperAttackAction :
    public Action
{
    Ball* mBall = nullptr;
    std::vector<Player*> mPlayers;

    sf::Vector2f getGoalPosition(Context::Team team, float y) const;
public:
    void Start(Player* player) override;
    void Update(Player* player) override;
    void End(Player* player) override;
};