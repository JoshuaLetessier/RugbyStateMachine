#include "pch.h"
#include "DebugController.h"

#include "GameManager.hpp"
#include "Player.hpp"
#include "Ball.hpp"
#include "Context.hpp"

#include "Utils.hpp"

DebugController::DebugController() {}

DebugController::~DebugController() {}

void DebugController::handleEvent(sf::RenderWindow* window)
{
    mWindow = window;
    sf::Event event;

    // Récupération unique des entités pour éviter des appels répétitifs
    mEntities = GameManager::GetEntities();

    while (mWindow->pollEvent(event))
    {
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
                selectEntity(event.mouseButton.x, event.mouseButton.y);
            if (event.mouseButton.button == sf::Mouse::Right)
                shootBall(event.mouseButton.x, event.mouseButton.y);
        }
        else if (event.type == sf::Event::Closed ||
            (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
        {
            mWindow->close();
        }
        else if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            releaseEntity();
        }
    }

    if (isDragging && selectedPlayer)
    {
        moveEntity();
    }
}

void DebugController::selectEntity(int mouseX, int mouseY)
{
    sf::Vector2f mousePos(mouseX, mouseY);

    for (auto& entity : mEntities)
    {
        Player* player = dynamic_cast<Player*>(entity);
        if (player && player->getShape().getGlobalBounds().contains(mousePos))
        {
            mState = player->getState();
            player->setState(Context::State::DEBUG);
            player->setDirection(sf::Vector2f(0, 0));
            selectedPlayer = player;
            isDragging = true;
            break;
        }
    }
}

void DebugController::moveEntity()
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(*mWindow);
    if (selectedPlayer)
    {
        selectedPlayer->setPosition(sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)));
    }
}

void DebugController::releaseEntity()
{
    isDragging = false;
    resetPlayerState();
}

void DebugController::shootBall(int mouseX, int mouseY)
{
    sf::Vector2f mousePos(mouseX, mouseY);

    // Récupération de la balle une seule fois
    selectedBall = Utils::GetBall(mEntities);
    if (selectedBall)
    {
        Player* ballKeeper = selectedBall->getPlayer();
        if (ballKeeper)
        {
            ballKeeper->setState(Context::State::IDLE);
            selectedBall->setPlayer(nullptr);
        }
        selectedBall->setPosition(sf::Vector2f(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)));
    }
}

void DebugController::resetPlayerState()
{
    if (selectedPlayer)
    {
        selectedPlayer->setState(mState);
        selectedPlayer = nullptr;
    }
}
