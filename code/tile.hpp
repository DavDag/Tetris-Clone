#pragma once
#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include "texturemanager.hpp"

#define DEBUG false

class Tile: public sf::Drawable, public sf::Transformable
{
    public:
        int x, y;
        Tile(){}
        Tile(int x, int y, int w, int h);
        void setColor(Textures::ID id);
        Textures::ID getColor();
        sf::FloatRect getBounds();
        void mark(bool marked);
        bool getMarked();
        bool isEmpty();
    private:
        virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;
        sf::Sprite sprite;
        bool marked;
        Textures::ID color;
};

#endif // TILE_HPP
