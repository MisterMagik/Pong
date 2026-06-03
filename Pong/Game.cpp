#include "Game.h"

Game::Game() {
    this->initWindow();
    this->initObjects();
    this->score1 = 0;
    this->score2 = 0;
    this->state = GS_LoginScreen; // Rozpoczynamy od ekranu logowania

    // Polaczenie z baza danych przy starcie
    // Zmien "root", "twoje_haslo", "nazwa_bazy" na wlasne dane konfiguracyjne MySQL
    this->dbManager.connect("tcp://127.0.0.1:3306", "root", "root", "pong_db");
}

Game::~Game() {
    // Przy zamykaniu gry zapisujemy aktualny stan punktów do bazy
    if (this->score1 > 0 || this->score2 > 0) {
        this->dbManager.saveScore(this->score1, this->score2);
    }
    this->dbManager.disconnect();

    delete this->window;
    delete this->player1;
    delete this->player2;
    delete this->ball;
}

void Game::initWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(800, 600), "SFML Pong", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
    this->windowSize = window->getSize();
}

void Game::initObjects() {
    this->player1 = new Paddle(20.f, 250.f);
    this->player2 = new Paddle(800.f - 40.f, 250.f);
    this->ball = new Ball(400.f, 300.f);
    this->addPowerUp();
}

const bool Game::running() const { return this->window->isOpen(); }

void Game::pollEvents() {
    while (this->window->pollEvent(this->ev)) {
        if (this->ev.type == sf::Event::Closed) this->window->close();

        // Przekazywanie wejscia do logowania tylko, gdy ten ekran jest aktywny
        if (this->state == GS_LoginScreen) {
            this->loginScreen.handleInput(this->ev, this->dbManager);
        }
    }
}

void Game::updateCollisions() {
    if (this->ball->getBounds().intersects(this->player1->getBounds())) {
        this->ball->bounceX();
    }
    if (this->ball->getBounds().intersects(this->player2->getBounds())) {
        this->ball->bounceX();
    }

    if (this->ball->getPosition().x < 0.f) {
        this->score2++;
        this->ball->reset(400.f, 300.f);
    }
    if (this->ball->getPosition().x > 800.f) {
        this->score1++;
        this->ball->reset(400.f, 300.f);
    }
}

void Game::update() {
    this->pollEvents();

    if (this->state == GS_LoginScreen) {
        this->loginScreen.update();
        if (this->loginScreen.isUserLoggedIn()) {
            this->state = GS_Playing; // Przechodzimy do gry po udanym zalogowaniu
        }
    }
    else if (this->state == GS_Playing) {
        bool p1Up = sf::Keyboard::isKeyPressed(sf::Keyboard::W);
        bool p1Down = sf::Keyboard::isKeyPressed(sf::Keyboard::S);
        this->player1->update(p1Up, p1Down, 600.f);

        bool p2Up = sf::Keyboard::isKeyPressed(sf::Keyboard::Up);
        bool p2Down = sf::Keyboard::isKeyPressed(sf::Keyboard::Down);
        this->player2->update(p2Up, p2Down, 600.f);

        this->ball->update(600.f);
        this->updateCollisions();
    }
}

void Game::render() {
    this->window->clear(sf::Color::Black);

    if (this->state == GS_LoginScreen) {
        this->loginScreen.render(this->window);
    }
    else if (this->state == GS_Playing) {
        this->player1->render(this->window);
        this->player2->render(this->window);
        this->ball->render(this->window);
        for (auto& powerUp : this->powerUps) {
            powerUp.render(this->window);
        }
    }

    this->window->display();
}

sf::Vector2u Game::getSize() {
    return this->window->getSize();
}

void Game::addPowerUp() {
    int posX = rand() % (this->windowSize.x - 50) + 25;
    int posY = rand() % (this->windowSize.y - 50) + 25;
    PowerUp newPowerUp(sf::Vector2f(posX, posY), PUT_SIZE);
    this->powerUps.push_back(newPowerUp);
}