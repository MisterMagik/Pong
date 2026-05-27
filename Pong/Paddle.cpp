#include "Paddle.h"

Paddle::Paddle(float startX, float startY) {
    this->shape.setSize(sf::Vector2f(20.f, 100.f)); 
    this->shape.setFillColor(sf::Color::White);
    this->shape.setPosition(startX, startY);
    this->movementSpeed = 7.f;
}

void Paddle::update(bool moveUp, bool moveDown, float windowHeight) {
    
    if (moveUp && this->shape.getPosition().y > 0.f) {
        this->shape.move(0.f, -this->movementSpeed);
    }
    
    if (moveDown && this->shape.getPosition().y + this->shape.getSize().y < windowHeight) {
        this->shape.move(0.f, this->movementSpeed);
    }
}

void Paddle::render(sf::RenderTarget* target) {
    target->draw(this->shape);
}

sf::FloatRect Paddle::getBounds() const {
    return this->shape.getGlobalBounds();
}