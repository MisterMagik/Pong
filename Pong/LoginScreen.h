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
    sf::Text registerText;
    sf::Text loginText;

    std::string usernameInput;
    std::string passwordInput;
    bool focusingPassword;
    bool isLogged;

    enum FocusedField {
		FIELD_LOGIN = 0,
		FIELD_PASSWORD,
		FIELD_REGISTER_BUTTON,
		FIELD_LOGIN_BUTTON,
        FIELD_COUNT
    };

    int activeField;

public:
    LoginScreen();
    void handleInput(sf::Event& ev, DatabaseManager& db);
    void update();
    void render(sf::RenderTarget* target);
    bool isUserLoggedIn() const { return isLogged; }
};