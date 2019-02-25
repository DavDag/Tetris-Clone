#include "game.hpp"
#include "gamestateditor.hpp"

int main()
{
    srand(time(NULL));

    Game game;

    game.pushState(new GameStateEditor(&game));
    game.gameLoop();

    return EXIT_SUCCESS;
}
