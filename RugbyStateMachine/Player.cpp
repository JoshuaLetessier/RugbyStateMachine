#include "pch.h"
#include "Player.hpp"
#include "./StateMachine/Behaviour.hpp"

#include <SFML/Graphics/CircleShape.hpp>
#include <iostream>

Player::Player(const sf::Vector2f& position, Behaviour* behaviour) :
    Entity(), mState(Context::State::IDLE)
{
    mBehaviour = behaviour;
	mSize = 50.f;
	mSpeed = 50.f;

    sf::CircleShape* shape = new sf::CircleShape(10);
	shape->setRadius(mSize / 2.f);
	shape->setFillColor(sf::Color::Green);
	shape->setOrigin(mSize / 2.f, mSize / 2.f);
	shape->setPosition(position);

	shape->setOutlineThickness(2.5f);
	shape->setOutlineColor(sf::Color::Transparent);


    mShape = shape;
}

Player::~Player()
{
	mBehaviour = nullptr;
}

void Player::Update()
{
	if (mBehaviour)
	{
		mBehaviour->Update(this);
	}
	Entity::Update();
	ExitWindowControl();

	// Gérer le temps d'étourdissement
	if (mTimeStunned > 0)
	{
		mTimeStunned -= GameManager::Get()->getDeltaTime();
		if (mTimeStunned <= 0)
		{
			mTimeStunned = 0;
		}
	}
}

Context::State Player::getState() const
{
    return mState;
}

void Player::setState(Context::State new_state) 
{
	if (mState != new_state)
	{
		mState = new_state;
		if (mBehaviour)
		{
			mBehaviour->Start(this);
		}
	}
}

Context::Team Player::getTeam() const
{
	return mTeam;
}

void Player::setTeam(Context::Team team)
{
	mTeam = team;
}

sf::Vector2f Player::getDirection() const
{
	return mDirection;
}

void Player::setTopLimit(int newTopLimit)
{
	mTopLimit = newTopLimit;
}

void Player::setBottomLimit(int newBottomLimit)
{
	mBottomLimit = newBottomLimit;
}

int Player::getTopLimit() const
{
	return mTopLimit;
}

int Player::getBottomLimit() const
{
	return mBottomLimit;
}

void Player::setInvisible(bool invisible)
{
	mIsInvisible = invisible;
}

bool Player::getIsInvisible() const
{
	return mIsInvisible;
}

void Player::setSpeed(float speed)
{
	mSpeed = speed;
}

void Player::setStunned(float time)
{
	mTimeStunned = time;
}

bool Player::isStunned() const
{
	return mTimeStunned > 0;
}

bool Player::isOnLimit()
{
	float position = getPosition().y;
	if (position < mTopLimit && position > mBottomLimit)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Player::ExitWindowControl()
{
	sf::Vector2f position = mShape->getPosition();

	// Check if the player is out of the window
	if (position.x < 0)
	{
		position.x = 0;
	}
	else if (position.x + mShape->getGlobalBounds().width > WINDOW_WIDTH)
	{
		position.x = WINDOW_WIDTH - mShape->getGlobalBounds().width;
	}
	if (position.y < 0)
	{
		position.y = 0;
	}
	else if (position.y + mShape->getGlobalBounds().height > WINDOW_HEIGHT)
	{
		position.y = WINDOW_HEIGHT - mShape->getGlobalBounds().height;
	}

	mShape->setPosition(position);
}