#pragma once

namespace sf 
{
	class Shape;
}

class Entity
{
protected:
    sf::Vector2f mDirection;
    float mSize;
	float mSpeed;

	sf::Shape* mShape;

    Entity();

public:
    virtual void Update();

    ~Entity();
    void setDirection(const sf::Vector2f& direction);
	const sf::Vector2f& getDirection() const;

    void goToPosition(const sf::Vector2f& position);
    void setPosition(const sf::Vector2f& position);
    const sf::Vector2f& getPosition() const;

	const float getSpeed() const;

    sf::Shape& getShape();
};
