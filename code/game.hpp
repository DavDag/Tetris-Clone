#pragma once
#ifndef GAME_HPP
#define GAME_HPP

#include <stack>
#include <SFML/Graphics.hpp>

class GameState;

class Game
{
    private:
        std::stack<GameState*> states;
        sf::Sprite bg;
        sf::View view;
    public:
        sf::RenderWindow window;
        Game();
        ~Game();
        int getSize();
        void pushState(GameState* state);
        void popState();
        void changeState(GameState* state);
        GameState* peekState();
        void gameLoop();
};

#endif // GAME_HPP

