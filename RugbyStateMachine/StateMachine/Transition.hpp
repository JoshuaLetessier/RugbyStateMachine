#pragma once

class Condition;
class Player;

class Transition
{
protected:
    Context::State mTargetState;
    std::vector<Condition*> mConditions;

public:
	virtual ~Transition();
    void Try(Player * Player);
    void setTargetState(Context::State target_state);
    void addCondition(Condition* condition);
};
