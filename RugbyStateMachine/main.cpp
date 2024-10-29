
#include "pch.h"

#include "GameManager.hpp"
#include "DebugController.h"

int main(void)
{
    srand(static_cast<unsigned int>(time(0)));

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "GamingCampus - Rugby - IA/StateMachines");
    window.setFramerateLimit(60);

    sf::Font font;
    if (!font.loadFromFile("./Hack-Regular.ttf"))
    {
        std::cerr << "Failed to load font" << std::endl;
        return -1;
    }

	GameManager * game_manager = GameManager::Instantiate();
    game_manager->setWindow(&window);
    game_manager->setDeltaTime(0.f);

	DebugController debugController;

    //Score text
	sf::Text scoreText;
	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(WINDOW_WIDTH / 2 - 100, 10);

	sf::RectangleShape greenGoal;
	sf::RectangleShape redGoal;

    constexpr float GOAL_WIDTH = 100.0f;          // Largeur du but
    constexpr float GOAL_HEIGHT = static_cast<float>(WINDOW_HEIGHT);

    // Initialisation du but vert (collé au bord gauche)
    greenGoal.setSize(sf::Vector2f(GOAL_WIDTH, GOAL_HEIGHT));
    greenGoal.setPosition(0, 0);  // Positionné directement sur le bord gauche
    greenGoal.setFillColor(sf::Color(139, 69, 19)); // Marron foncé

    // Initialisation du but rouge (collé au bord droit)
    redGoal.setSize(sf::Vector2f(GOAL_WIDTH, GOAL_HEIGHT));
    redGoal.setPosition(WINDOW_WIDTH - GOAL_WIDTH, 0); // Positionné directement sur le bord droit
    redGoal.setFillColor(sf::Color(139, 69, 19)); // Marron foncé


    sf::Clock clock;
    while (window.isOpen())
    {
        sf::Time dt = clock.restart();
        sf::Event event;
#ifdef _DEBUG
		debugController.handleEvent(&window);
#endif
        window.clear();
        window.clear(sf::Color(51, 153, 102));

        window.draw(greenGoal);
        window.draw(redGoal);

        game_manager->Update();
        game_manager->Draw();


        std::string scoreDisplay = "Score Green: " + std::to_string(game_manager->getScoreGreen()) + " - Score Red: " + std::to_string(game_manager->getScoreRed());
        scoreText.setString(scoreDisplay);
		window.draw(scoreText);

        window.display();

        game_manager->setDeltaTime(dt.asSeconds());
    }

	delete game_manager;

#ifdef _DEBUG
    _CrtDumpMemoryLeaks();
#endif

	return 0;
}
