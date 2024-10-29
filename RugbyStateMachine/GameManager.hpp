#pragma once

class Entity;
class Ball;
class Behaviour;
class Transition;

namespace sf
{
	class RenderWindow;
}

class GameManager
{
	std::vector<Entity*> mEntities;
	sf::RenderWindow* mWindow;
	float mDeltaTime;
	Behaviour* mBehaviour;

	int mScoreRed = 0;
	int mScoreGreen = 0;

	bool mIsWin = false;

	std::vector<sf::Vector2f> team1Positions;
	std::vector<sf::Vector2f> team2Positions;

	GameManager();

	void addEntity(Entity* entity);

public:
	~GameManager();

	static GameManager* Instantiate();
	static GameManager* Get();
	static Ball* GetBall();
	static std::vector<Player*> GetPlayers();
	static std::vector<Player*> GetPlayersByTeam(Context::Team team);

	static void setScoreRed(int score);
	static void setScoreGreen(int score);
	static int getScoreRed();
	static int getScoreGreen();

	static void setWin();
	static bool getWin();

	void Update();
	void Draw();

	void initPlayers();
	void initTeamPlayers(Context::Team team, const std::vector<sf::Vector2f>& positions, const sf::Color& color);
	void definePlayerLimits(Player* player, int index);
	void assignBallToRandomPlayer(Context::Team team);
	void initActions();
	void initTransitions();
	void addTransition(Context::State fromState, Context::State toState, Condition* condition);
	void resetPositions();

	void resetTeamPositions(const std::vector<Player*>& players, const std::vector<sf::Vector2f>& positions);

	void setWindow(sf::RenderWindow* window);
	void setDeltaTime(float deltaTime);
	float getDeltaTime() const;

	static std::vector<Entity*> GetEntities();
	std::vector<Entity*> thisGetEntites();

	friend Entity;
};
