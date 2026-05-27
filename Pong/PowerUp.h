#pragma once
#include <SFML/Graphics.hpp>


enum PowerUpType {
	PUT_SIZE = 0,
	PUT_SPEED
};
class PowerUp
{
private:
	sf::RectangleShape shape;
	sf::Vector2f position;
	int type;

public:
	PowerUp(sf::Vector2f position, int type);
	~PowerUp();
	void render(sf::RenderTarget* target);


};

