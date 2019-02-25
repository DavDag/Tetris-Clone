#pragma once
#ifndef GAMESTATE_HPP
#define GAMESTATE_HPP

#include <SFML/Graphics.hpp>
#include "game.hpp"

class GameState
{
    public:
        Game* game;
        virtual void update(sf::Time dt) = 0;
        virtual void draw() = 0;
        virtual void handleInput() = 0;
        virtual std::string getName() = 0;
};

#endif // GAMESTATE_HPP
