#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{

	srand(time(NULL));
    Game game;

    while (game.running()) {
        game.update();
        game.render();
    }
  

    return 0;
}