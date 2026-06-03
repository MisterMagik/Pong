#pragma once
#include <SFML/Graphics.hpp>
#include "DatabaseManager.h"

class LoginScreen {
private:
    sf::Font font;
    sf::Text titleText;
    sf::Text loginLabel;
    sf::Text passLabel;
    sf::Text infoText;
    sf::Text instructionText;

    std::string usernameInput;
    std::string passwordInput;
    bool focusingPassword;
    bool isLogged;

public:
    LoginScreen();
    void handleInput(sf::Event& ev, DatabaseManager& db);
    void update();
    void render(sf::RenderTarget* target);
    bool isUserLoggedIn() const { return isLogged; }
};