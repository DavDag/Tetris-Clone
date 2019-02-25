#pragma once
#ifndef STATUS_HPP
#define STATUS_HPP

#include <SFML/Graphics.hpp>

class GameStateStart;

class Status: public sf::Drawable, public sf::Transformable
{
    public:
        Status(GameStateStart* game);
        void addScore(int increment);
        void addLine(int increment);
        void addLevel(int increment);
        int getLevel();
    private:
        virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;
        GameStateStart* game;
        sf::Text score, line, level;
        int pscore, pline, plevel;
        sf::RectangleShape bg;
};

#endif // STATUS_HPP
