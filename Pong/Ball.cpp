#include "Ball.h"

Ball::Ball(float startX, float startY) {
    this->shape.setRadius(10.f); 
    this->shape.setFillColor(sf::Color::White);
    this->initSpeed = 5.f;
    this->reset(startX, startY);
}

void Ball::reset(float startX, float startY) {
    this->shape.setPosition(startX, startY);
    
    this->velocity.x = this->initSpeed;
    this->velocity.y = this->initSpeed * 0.5f;
}

void Ball::update(float windowHeight) {
    this->shape.move(this->velocity);

    
    if (this->shape.getPosition().y <= 0.f || this->shape.getPosition().y + this->shape.getRadius() * 2 >= windowHeight) {
        this->bounceY();
    }
}

void Ball::render(sf::RenderTarget* target) {
    target->draw(this->shape);
}

void Ball::bounceX() { this->velocity.x = -this->velocity.x; }
void Ball::bounceY() { this->velocity.y = -this->velocity.y; }

sf::FloatRect Ball::getBounds() const { return this->shape.getGlobalBounds(); }
sf::Vector2f Ball::getPosition() const { return this->shape.getPosition(); }