#include "pch.h"
#include "Entity.hpp"

#include "GameManager.hpp"
#include "Utils.hpp"

#include <SFML/Graphics/Shape.hpp>

Entity::Entity()
{ 
}

Entity::~Entity()
{
	delete mShape;
}

void Entity::Update()
{
    float dt = GameManager::Get()->getDeltaTime();

    sf::Vector2f newPosition;
    newPosition.x += dt * mSpeed * mDirection.x;
    newPosition.y += dt * mSpeed * mDirection.y;
    mShape->move(newPosition);
}

void Entity::setPosition(const sf::Vector2f& position)
{
    mShape->setPosition(position);
}

const sf::Vector2f& Entity::getPosition() const
{
    return mShape->getPosition();
}

void Entity::setDirection(const sf::Vector2f& new_direction)
{
    mDirection = new_direction;
}

const sf::Vector2f& Entity::getDirection() const
{
	return mDirection;
}

void Entity::goToPosition(const sf::Vector2f& position)
{
    setDirection(Utils::Vector2Normalize(position - getPosition()));
}

const float Entity::getSpeed() const
{
	return mSpeed;
}

sf::Shape& Entity::getShape()
{
    return *mShape;
}
