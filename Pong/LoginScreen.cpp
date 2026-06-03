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

	this->registerText.setFont(this->font);
	this->registerText.setCharacterSize(14);
	this->registerText.setPosition(180.f, 400.f);
	this->registerText.setFillColor(sf::Color::White);
	this->registerText.setString("Zarejestruj");

    this->loginText.setFont(this->font);
    this->loginText.setCharacterSize(14);
    this->loginText.setPosition(400.f, 400.f);
    this->loginText.setFillColor(sf::Color::White);
    this->loginText.setString("Zaloguj");

    this->instructionText.setFont(this->font);
    this->instructionText.setCharacterSize(14);
    this->instructionText.setString("TAB: Przelacz pole | ENTER: Zatwierdz");
    this->instructionText.setPosition(180.f, 480.f);
    this->instructionText.setFillColor(sf::Color::White);
}

void LoginScreen::handleInput(sf::Event& ev, DatabaseManager& db) {
    if (ev.type == sf::Event::KeyPressed) {
        // Prze³¹czanie miêdzy 4 polami za pomoc¹ TAB
        if (ev.key.code == sf::Keyboard::Tab) {
            this->activeField = (this->activeField + 1) % FIELD_COUNT;
            this->infoText.setString(""); // Czyszczenie info przy zmianie pola
        }
        // Enter aktywuje akcjê w zale¿noœci od tego, gdzie stoi kursor ">"
        else if (ev.key.code == sf::Keyboard::Enter) {

            // Opcja A: Kursor na polu Login, polu Has³a lub bezpoœrednio na "Zaloguj" -> Logujemy!
            if (this->activeField == FIELD_LOGIN || this->activeField == FIELD_PASSWORD || this->activeField == FIELD_LOGIN_BUTTON) {
                if (db.loginUser(this->usernameInput, this->passwordInput)) {
                    this->isLogged = true;
                }
                else {
                    this->infoText.setFillColor(sf::Color::Red);
                    this->infoText.setString("Bledny login lub haslo!");
                }
            }
            // Opcja B: Kursor na przycisku "Zarejestruj" -> Rejestrujemy!
            else if (this->activeField == FIELD_REGISTER_BUTTON) {
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
    }

    // Wpisywanie tekstu dzia³a TYLKO, gdy aktywne jest pole login lub has³o
    if (ev.type == sf::Event::TextEntered) {
        if (this->activeField == FIELD_LOGIN || this->activeField == FIELD_PASSWORD) {
            std::string* currentInput = (this->activeField == FIELD_PASSWORD) ? &this->passwordInput : &this->usernameInput;

            if (ev.text.unicode == 8) { // Backspace
                if (!currentInput->empty()) {
                    currentInput->pop_back();
                }
            }
            // Bezpieczne filtrowanie znaków drukowalnych (bez TAB, Enter, itp.)
            else if (ev.text.unicode >= 32 && ev.text.unicode <= 126) {
                if (currentInput->length() < 15) { // Ograniczenie d³ugoœci tekstu
                    *currentInput += static_cast<char>(ev.text.unicode);
                }
            }
        }
    }
}


void LoginScreen::update() {
    // Aktualizacja Pola 1: Login
    if (this->activeField == FIELD_LOGIN) {
        this->loginLabel.setString("> Login: " + this->usernameInput);
        this->loginLabel.setFillColor(sf::Color::Yellow);
    }
    else {
        this->loginLabel.setString("  Login: " + this->usernameInput);
        this->loginLabel.setFillColor(sf::Color::White);
    }

    // Aktualizacja Pola 2: Has³o
    std::string maskedPassword(this->passwordInput.length(), '*');
    if (this->activeField == FIELD_PASSWORD) {
        this->passLabel.setString("> Haslo: " + maskedPassword);
        this->passLabel.setFillColor(sf::Color::Yellow);
    }
    else {
        this->passLabel.setString("  Haslo: " + maskedPassword);
        this->passLabel.setFillColor(sf::Color::White);
    }

    // Aktualizacja Pola 3: Przycisk Zaloguj
    if (this->activeField == FIELD_LOGIN_BUTTON) {
        this->loginText.setString("> [ ZALOGUJ SIE ]");
        this->loginText.setFillColor(sf::Color::Cyan);
    }
    else {
        this->loginText.setString("  [ ZALOGUJ SIE ]");
        this->loginText.setFillColor(sf::Color::White);
    }

    // Aktualizacja Pola 4: Przycisk Zarejestruj
    if (this->activeField == FIELD_REGISTER_BUTTON) {
        this->registerText.setString("> [ ZAREJESTRUJ KONTO ]");
        this->registerText.setFillColor(sf::Color::Cyan);
    }
    else {
        this->registerText.setString("  [ ZAREJESTRUJ KONTO ]");
        this->registerText.setFillColor(sf::Color::White);
    }
}

void LoginScreen::render(sf::RenderTarget* target) {
    target->draw(this->titleText);
    target->draw(this->loginLabel);
    target->draw(this->passLabel);
    target->draw(this->infoText);
    target->draw(this->instructionText);
	target->draw(this->registerText);
    target->draw(this->loginText);
}