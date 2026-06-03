#include "PowerUp.h"

PowerUp::PowerUp(sf::Vector2f position, int type)
{
	this->shape.setFillColor(sf::Color::Yellow);
	this->shape.setSize(sf::Vector2f(20.f, 20.f));
	this->shape.setPosition(position);
	this->type = type;

}

PowerUp::~PowerUp()
{

}

void PowerUp::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}
