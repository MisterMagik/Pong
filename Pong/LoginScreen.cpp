#include "LoginScreen.h"

LoginScreen::LoginScreen() {
    if (!this->font.loadFromFile("assets/fonts/arial.ttf")) {
        // todo
    }

    this->focusingPassword = false;
    this->isLogged = false;

    this->titleText.setFont(this->font);
    this->titleText.setString("LOGOWANIE / REJESTRACJA");
    this->titleText.setCharacterSize(34);
    this->titleText.setPosition(180.f, 80.f);
    this->titleText.setFillColor(sf::Color::Cyan);

    this->loginLabel.setFont(this->font);
    this->loginLabel.setCharacterSize(22);
    this->loginLabel.setPosition(180.f, 220.f);

    this->passLabel.setFont(this->font);
    this->passLabel.setCharacterSize(22);
    this->passLabel.setPosition(180.f, 280.f);

    this->infoText.setFont(this->font);
    this->infoText.setCharacterSize(18);
    this->infoText.setPosition(180.f, 360.f);
    this->infoText.setFillColor(sf::Color::Yellow);

    this->instructionText.setFont(this->font);
    this->instructionText.setCharacterSize(14);
    this->instructionText.setString("TAB: Przelacz pole | ENTER: Zaloguj | R: Zarejestruj konto");
    this->instructionText.setPosition(180.f, 480.f);
    this->instructionText.setFillColor(sf::Color::White);
}

void LoginScreen::handleInput(sf::Event& ev, DatabaseManager& db) {
    if (ev.type == sf::Event::KeyPressed) {
        if (ev.key.code == sf::Keyboard::Tab) {
            this->focusingPassword = !this->focusingPassword;
        }
        else if (ev.key.code == sf::Keyboard::Enter) {
            if (db.loginUser(this->usernameInput, this->passwordInput)) {
                this->isLogged = true;
            }
            else {
                this->infoText.setFillColor(sf::Color::Red);
                this->infoText.setString("Bledny login lub haslo!");
            }
        }
        else if (ev.key.code == sf::Keyboard::R) {
            if (!this->usernameInput.empty() && !this->passwordInput.empty()) {
                if (db.registerUser(this->usernameInput, this->passwordInput)) {
                    this->infoText.setFillColor(sf::Color::Green);
                    this->infoText.setString("Zarejestrowano! Mozesz sie zalogowac.");
                }
                else {
                    this->infoText.setFillColor(sf::Color::Red);
                    this->infoText.setString("Ta nazwa uzytkownika jest juz zajeta!");
                }
            }
            else {
                this->infoText.setFillColor(sf::Color::Red);
                this->infoText.setString("Pola nie moga byc puste!");
            }
        }
    }

    if (ev.type == sf::Event::TextEntered) {
        if (ev.text.unicode < 128) {
            std::string* currentInput = this->focusingPassword ? &this->passwordInput : &this->usernameInput;

            if (ev.text.unicode == 8) { // Backspace
                if (!currentInput->empty()) {
                    currentInput->pop_back();
                }
            }
            // Ignorujemy Tab (9) i Enter (13), bo obslugujemy je wyzej
            else if (ev.text.unicode != 13 && ev.text.unicode != 9 && ev.text.unicode != 27) {
                *currentInput += static_cast<char>(ev.text.unicode);
            }
        }
    }
}

void LoginScreen::update() {
    this->loginLabel.setString((!this->focusingPassword ? "> Login: " : "  Login: ") + this->usernameInput);

    std::string maskedPassword(this->passwordInput.length(), '*');
    this->passLabel.setString((this->focusingPassword ? "> Haslo: " : "  Haslo: ") + maskedPassword);
}

void LoginScreen::render(sf::RenderTarget* target) {
    target->draw(this->titleText);
    target->draw(this->loginLabel);
    target->draw(this->passLabel);
    target->draw(this->infoText);
    target->draw(this->instructionText);
}