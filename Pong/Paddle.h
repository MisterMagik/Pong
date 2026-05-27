#pragma once
#include <SFML/Graphics.hpp>

class Paddle {
private:
    sf::RectangleShape shape;
    float movementSpeed;

public:
    Paddle(float startX, float startY);

    void update(bool moveUp, bool moveDown, float windowHeight);
    void render(sf::RenderTarget* target);

    
    sf::FloatRect getBounds() const;
};