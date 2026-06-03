#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"
#include <vector>
#include "PowerUp.h"
#include "DataBaseManager.h"


enum GameState {
    GS_MainMenu = 0,
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
    
    DatabaseManager dbManager;

    int score1;
    int score2;

    void initWindow();
    void initObjects();
	void addPowerUp();
	void updatePowerUps();

	std::vector<PowerUp> powerUps;

	sf::Vector2u windowSize;


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