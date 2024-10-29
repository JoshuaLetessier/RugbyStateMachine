#pragma once

class Behaviour;

class Player : public Entity
{
	Context::State mState;
	Behaviour *mBehaviour;

	Context::Team mTeam;

	int mTopLimit = 0;
	int mBottomLimit = 0;

	bool mIsInvisible = false;
	// time of invisibility
	int mInvisibleTime = 3;
	int topLimit = 0;
	int bottomLimit = 0;
	float mTimeStunned = 0.f;

public:
	Player(const sf::Vector2f &position, Behaviour *behaviour);
	~Player();

	void Update() override;

	Context::State getState() const;
	void setState(Context::State);

	Context::Team getTeam() const;
	void setTeam(Context::Team team);

	sf::Vector2f getDirection() const;

	void setTopLimit(int mTopLimit);
	void setBottomLimit(int mBottomLimit);
	int getTopLimit() const;
	int getBottomLimit() const;
	void setStunned(float time);
	bool isStunned() const;

	void setInvisible(bool invisible);
	bool getIsInvisible() const;

	void setSpeed(float speed);

	bool isOnLimit();
	void ExitWindowControl();
};
