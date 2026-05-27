#pragma once
#include <SFML/Graphics.hpp>
#include "Paddle.h"
#include "Ball.h"

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

    int score1;
    int score2;

    void initWindow();
    void initObjects();

public:
    Game();
    virtual ~Game();

    const bool running() const;
    void pollEvents();
    void updateCollisions();
    void update();
    void render();
};