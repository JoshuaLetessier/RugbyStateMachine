#include "../pch.h"
#include "Transition.hpp"
#include "../Player.hpp"

Transition::~Transition()
{
    for (auto c : mConditions)
    {
        delete c;
    }
	mConditions.clear();
}

void Transition::setTargetState(Context::State target_state)
{
    mTargetState = target_state;
}

void Transition::addCondition(Condition* condition)
{
    mConditions.push_back(condition);
}

void Transition::Try(Player * player)
{
    int true_tests = 0;
    for (const auto &c : mConditions)
    {
        true_tests += c->Test(player);
    }
    if (true_tests != 0 && true_tests == mConditions.size())
    {
        player->setState(mTargetState);
#ifdef _DEBUG
        if (mTargetState == Context::State::BALLKEEPER)
        {
			player->getShape().setOutlineColor(sf::Color::Yellow);
        }
        else if (mTargetState == Context::State::ATTACK)
        {
            player->getShape().setOutlineColor(sf::Color::Blue);
        }
		else if (mTargetState == Context::State::DEFEND)
		{
			player->getShape().setOutlineColor(sf::Color::Black);
		}
		else if (mTargetState == Context::State::IDLE)
		{
			player->getShape().setOutlineColor(sf::Color::Magenta);
		}
#endif // DEBUG
    }
}
