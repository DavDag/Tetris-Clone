#pragma once
#ifndef PIECE_HPP
#define PIECE_HPP

#include <SFML/Graphics.hpp>
#include "tile.hpp"
#include "texturemanager.hpp"

namespace Pieces{
    enum ID{I, J, L, O, S, T, Z};
}

class Piece: public sf::Drawable, public sf::Transformable
{
    public:
        Piece(){}
        Piece(Pieces::ID type, Textures::ID color);
        sf::FloatRect getBounds() const;
        Textures::ID getColor();
        Pieces::ID getType();
        bool check(sf::FloatRect rect);
        void rotate();
        std::vector<Tile>& getTiles();
    private:
        virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;
        std::vector<Tile> tiles;
        Textures::ID color;
        Pieces::ID type;
};

#endif // PIECE_HPP
