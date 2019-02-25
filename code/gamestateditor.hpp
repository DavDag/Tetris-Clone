#pragma once
#ifndef GAMESTATEEDITOR_HPP
#define GAMESTATEEDITOR_HPP

#include <SFML/Graphics.hpp>
#include "gamestate.hpp"
#include "button.hpp"

class GameStateEditor: public GameState
{
    private:
        Button Bplay, Bsettings;
    public:
        GameStateEditor(Game* game);
        virtual void update(sf::Time dt);
        virtual void draw();
        virtual void handleInput();
        virtual std::string getName();
};

#endif // GAMESTATEEDITOR_HPP
