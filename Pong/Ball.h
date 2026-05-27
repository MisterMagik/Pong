#pragma once
#include <SFML/Graphics.hpp>

class Ball {
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    float initSpeed;

public:
    Ball(float startX, float startY);

    void update(float windowHeight);
    void render(sf::RenderTarget* target);

    void bounceX(); // Odbicie lewo/prawo
    void bounceY(); // Odbicie góra/dó³
    void reset(float startX, float startY);

    sf::FloatRect getBounds() const;
    sf::Vector2f getPosition() const;
};