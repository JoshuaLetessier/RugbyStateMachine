#include "pch.h"
#include "./StateMachine/Behaviour.hpp"
#include "Player.hpp"
#include "Ball.hpp"
#include "./StateMachine/Transition.hpp"
#include "GameManager.hpp"

// Defense
#include "Action/DefenserFollowBallAction.h"
#include "Action/DefenserTakeBallAction.h"
#include "Condition/AnyToBallKeeperCondition.h"
#include "Condition/IdleToDefenserCondition.hpp"
#include "Condition/DefenseToAttackCondition.h"

// Attack
#include "Action/AttackFollowBallKeeperAction.h"
#include "Condition/AttackToDefenseCondition.h"
#include "Condition/IdleToAttackerCondition.hpp"

#include "Condition/BallKeeperToIdleCondition.hpp"
#include "Condition/IdleToBallKeeperCondition.hpp"

#include "Action/IdleWaitAction.hpp"
#include "Action/BallKeeperAttackAction.hpp"
#include "Action/BallKeeperPassAction.hpp"
#include "Action/BallKeeperTryoutAction.hpp"

namespace
{
	static GameManager *mInstance = nullptr;
}

GameManager::GameManager() : mDeltaTime(0.f), mWindow(nullptr), mBehaviour(nullptr)
{
	mBehaviour = new Behaviour();
}

GameManager::~GameManager()
{
	for (int i = 0; i < mEntities.size(); i++)
	{
		delete mEntities[i];
	}
	mEntities.clear();

	delete mBehaviour;
}

GameManager *GameManager::Instantiate()
{
	if (!mInstance)
	{
		mInstance = new GameManager();

		mInstance->initActions();
		mInstance->initTransitions();
		mInstance->initPlayers();

		return mInstance;
	}
	return nullptr;
}

GameManager *GameManager::Get()
{
	return mInstance;
}

Ball *GameManager::GetBall()
{

	for (Entity *entity : mInstance->mEntities)
	{
		Ball *ball = dynamic_cast<Ball *>(entity);
		if (ball)
		{
			return ball;
		}
	}
	return nullptr;
}

std::vector<Player *> GameManager::GetPlayers()
{
	std::vector<Player *> players;
	for (Entity *entity : GameManager::Get()->mEntities)
	{
		Player *player = dynamic_cast<Player *>(entity);
		if (player)
		{
			players.push_back(player);
		}
	}
	return players;
}

std::vector<Player*> GameManager::GetPlayersByTeam(Context::Team team)
{
	std::vector<Player*> players;
	for (Entity* entity : mInstance->mEntities)
	{
		Player* player = dynamic_cast<Player*>(entity);
		if (player && player->getTeam() == team)
		{
			players.push_back(player);
		}
	}
	return players;
}

void GameManager::setScoreRed(int score)
{
	mInstance->mScoreRed += score;
}

void GameManager::setScoreGreen(int score)
{
	mInstance->mScoreGreen += score;
}

int GameManager::getScoreRed()
{
	return mInstance->mScoreRed;
}

int GameManager::getScoreGreen()
{
	return mInstance->mScoreGreen;
}

void GameManager::setWin()
{
	mInstance->mIsWin = true;
}

bool GameManager::getWin()
{
	return mInstance->mIsWin;
}

void GameManager::setWindow(sf::RenderWindow *window)
{
	mWindow = window;
}

void GameManager::Update()
{
	if (mInstance->mIsWin)
	{
		mInstance->mIsWin = false;
		resetPositions();
	}

	for (Entity *entity : mEntities)
	{
		entity->Update();
	}
}

void GameManager::Draw()
{
	for (Entity *entity : mEntities)
	{
		mWindow->draw(entity->getShape());
	}
}

void GameManager::initPlayers()
{
	// Equipe 1 (Vert)
	team1Positions = {
		sf::Vector2f(50, 50),
		sf::Vector2f(150, 100),
		sf::Vector2f(250, 360),
		sf::Vector2f(150, 630),
		sf::Vector2f(50, 680)};

	// Team 2 (RED)
	team2Positions = {
		sf::Vector2f(1180, 50),
		sf::Vector2f(1080, 100),
		sf::Vector2f(980, 360),
		sf::Vector2f(1080, 630),
		sf::Vector2f(1180, 680)};

	initTeamPlayers(Context::Team::GREEN, team1Positions, sf::Color::Green);
	initTeamPlayers(Context::Team::RED, team2Positions, sf::Color::Red);

	Ball* ball = new Ball(sf::Vector2f(640, 360));
	mEntities.push_back(ball);

	//radom team to start with the ball

	assignBallToRandomPlayer(Context::Team::GREEN);
}

void GameManager::initTeamPlayers(Context::Team team, const std::vector<sf::Vector2f>& positions, const sf::Color& color)
{
	for (int i = 0; i < positions.size(); ++i)
	{
		Player* player = new Player(positions[i], mBehaviour);
		player->setTeam(team);
		player->getShape().setFillColor(color);

		definePlayerLimits(player, i); // Sets top/bottom limits for each player based on index

		mEntities.push_back(player);
	}
}

void GameManager::definePlayerLimits(Player* player, int index)
{
	if (index < 2)
	{
		player->setTopLimit(240);
		player->setBottomLimit(0);
	}
	else if (index == 2)
	{
		player->setTopLimit(480);
		player->setBottomLimit(240);
	}
	else
	{
		player->setTopLimit(720);
		player->setBottomLimit(480);
	}
}

void GameManager::assignBallToRandomPlayer(Context::Team team)
{
	std::vector<Player*> players = GetPlayersByTeam(team);
	if (!players.empty())
	{
		Player* player = players[rand() % players.size()];
		Ball* ball = GetBall();
		if (ball)
		{
			ball->setPosition(player->getPosition());
			ball->setPlayer(player);
		}
	}
}

void GameManager::initActions()
{
	mBehaviour->AddAction(Context::State::DEFEND, new DefenserTakeBallAction());
	mBehaviour->AddAction(Context::State::DEFEND, new DefenserFollowBallAction());

	mBehaviour->AddAction(Context::State::ATTACK, new AttackFollowBallKeeperAction());

	mBehaviour->AddAction(Context::State::BALLKEEPER, new BallKeeperTryoutAction());
	mBehaviour->AddAction(Context::State::BALLKEEPER, new BallKeeperAttackAction());
	mBehaviour->AddAction(Context::State::BALLKEEPER, new BallKeeperPassAction());

	mBehaviour->AddAction(Context::State::IDLE, new IdleWaitAction());
}

void GameManager::initTransitions()
{
	addTransition(Context::State::DEFEND, Context::State::BALLKEEPER, new AnyToBallKeeperCondition());
	addTransition(Context::State::DEFEND, Context::State::ATTACK, new DefenseToAttackCondition());
	addTransition(Context::State::ATTACK, Context::State::BALLKEEPER, new AnyToBallKeeperCondition());
	addTransition(Context::State::ATTACK, Context::State::DEFEND, new AttackToDefenseCondition());
	addTransition(Context::State::BALLKEEPER, Context::State::IDLE, new BallKeeperToIdleCondition());
	addTransition(Context::State::IDLE, Context::State::BALLKEEPER, new IdleToBallKeeperCondition());
	addTransition(Context::State::IDLE, Context::State::DEFEND, new IdleToDefenserCondition());
	addTransition(Context::State::IDLE, Context::State::ATTACK, new IdleToAttackerCondition());
}

void GameManager::addTransition(Context::State fromState, Context::State toState, Condition* condition)
{
	Transition* transition = new Transition();
	transition->setTargetState(toState);
	transition->addCondition(condition);
	mBehaviour->AddTransition(fromState, transition);
}

void GameManager::resetPositions()
{
	resetTeamPositions(GetPlayersByTeam(Context::Team::GREEN), team1Positions);
	resetTeamPositions(GetPlayersByTeam(Context::Team::RED), team2Positions);

	Ball* ball = GetBall();
	if (ball && ball->getPlayer())
	{
		Context::Team teamColor = ball->getPlayer()->getTeam();
		ball->getPlayer()->setSpeed(50.f);
		assignBallToRandomPlayer(ball->getPlayer()->getTeam() == Context::Team::GREEN ? Context::Team::RED : Context::Team::GREEN);
	}
}

void GameManager::resetTeamPositions(const std::vector<Player*>& players, const std::vector<sf::Vector2f>& positions)
{
	if (players.size() == positions.size())
	{
		for (size_t i = 0; i < players.size(); ++i)
		{
			players[i]->setPosition(positions[i]);
		}
	}
}

void GameManager::setDeltaTime(float deltaTime)
{
	mDeltaTime = deltaTime;
}

float GameManager::getDeltaTime() const
{
	return mDeltaTime;
}

std::vector<Entity *> GameManager::GetEntities()
{
	return mInstance->mEntities;
}

std::vector<Entity*> GameManager::thisGetEntites()
{
	return mEntities;
}

void GameManager::addEntity(Entity *entity)
{
	mEntities.push_back(entity);
}