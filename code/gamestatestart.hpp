#pragma once
#ifndef GAMESTATESTART_HPP
#define GAMESTATESTART_HPP

#include <SFML/Graphics.hpp>
#include "gamestate.hpp"
#include "button.hpp"
#include "status.hpp"
#include "board.hpp"

class GameStateStart: public GameState
{
    private:
        Button Bback, Bpause;
        Status status;
        Board board;
        sf::Text msg;
    public:
        GameStateStart(Game* game);
        bool ended, paused;
        virtual void update(sf::Time dt);
        virtual void draw();
        virtual void handleInput();
        virtual std::string getName();
        void restart();
        void placed();
};

#endif // GAMESTATESTART_HPP
