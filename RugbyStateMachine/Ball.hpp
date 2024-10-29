#pragma once

class Player;

class Ball : public Entity
{
public:
    Ball(const sf::Vector2f& position);
    ~Ball();

    void Update() override;

	void ExitWindowControl();

	void setPlayer(Player* player);
	Player* getPlayer() const;

private:
	Player* mPlayer;
};
