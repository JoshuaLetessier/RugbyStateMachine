#pragma once

class Action;

class IdleWaitAction :
    public Action
{
public:
    void Start(Player* player) override;
    void Update(Player* player) override;
    void End(Player* player) override;
};

