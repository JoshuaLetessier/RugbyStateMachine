#include "pch.h"
#include "Ball.hpp"
#include "Player.hpp"

Ball::Ball(const sf::Vector2f& position) : Entity()
{
    sf::CircleShape* shape = new sf::CircleShape();
    mSize = 30.f;
	mSpeed = 100.f;

    shape->setRadius(mSize / 2.f);
    shape->setFillColor(sf::Color::Yellow);
    shape->setOrigin(mSize / 2.f, mSize / 2.f);
    shape->setPosition(position);
    mShape = shape;
}

Ball::~Ball()
{
}

void Ball::Update()
{
    Entity::Update();
    ExitWindowControl();
}

void Ball::ExitWindowControl()
{
    sf::Vector2f position = mShape->getPosition();
	sf::Vector2f direction = getDirection();

    // Contrôle des limites gauche et droite
    if (position.x < 0)
    {
        position.x = 0;            // Replace la balle au bord gauche
        direction.x = -direction.x; // Inverse la direction horizontale
    }
    else if (position.x + mShape->getGlobalBounds().width > WINDOW_WIDTH)
    {
        position.x = WINDOW_WIDTH - mShape->getGlobalBounds().width; // Replace au bord droit
        direction.x = -direction.x; // Inverse la direction horizontale
    }

    // Contrôle des limites haut et bas
    if (position.y < 0)
    {
        position.y = 0;            // Replace la balle en haut
        direction.y = -direction.y; // Inverse la direction verticale
    }
    else if (position.y + mShape->getGlobalBounds().height > WINDOW_HEIGHT)
    {
        position.y = WINDOW_HEIGHT - mShape->getGlobalBounds().height; // Replace en bas
        direction.y = -direction.y; // Inverse la direction verticale
    }

    // Mise à jour de la position et de la direction
    mShape->setPosition(position);
    setDirection(direction); // Met à jour la direction de la balle
}

void Ball::setPlayer(Player* player)
{
	mPlayer = player;
}

Player* Ball::getPlayer() const
{
    return mPlayer;
}

