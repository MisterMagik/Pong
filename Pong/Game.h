#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"
#include <vector>
#include "PowerUp.h"
#include "DatabaseManager.h"
#include "LoginScreen.h"

enum GameState {
    GS_LoginScreen = 0,
    GS_MainMenu,
    GS_Playing,
    GS_Pause,
    GS_GameOver
};

class Game {
private:
    sf::RenderWindow* window;
    sf::Event ev;

    Paddle* player1;
    Paddle* player2;
    Ball* ball;

    int score1;
    int score2;

    void initWindow();
    void initObjects();
    void addPowerUp();
    void updatePowerUps();

    std::vector<PowerUp> powerUps;
    sf::Vector2u windowSize;

    // Elementy bazy danych i stanu gry
    GameState state;
    DatabaseManager dbManager;
    LoginScreen loginScreen;

public:
    Game();
    virtual ~Game();

    const bool running() const;
    void pollEvents();
    void updateCollisions();
    void update();
    void render();
    sf::RenderWindow* getWindow() const { return this->window; }
    sf::Vector2u getSize();
};