#pragma once
#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include "piece.hpp"
#include "tile.hpp"
#include "texturemanager.hpp"
#include "effect.hpp"

#define ROWS 18

class GameStateStart;

namespace Directions
{
    enum ID{Left, Right, Down, Up};
}

class Board: public sf::Drawable, public sf::Transformable
{
    public:
        Board(GameStateStart* game);
        void createPiece();
        void update(sf::Time dt, int diff);
        void collide();
        void place(Textures::ID color);
        void movePiece(Directions::ID dir);
        bool checkCollision();
        void rotatePiece();
        int eraseLines();
    private:
        virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;
        GameStateStart* game;
        sf::RectangleShape bg;
        Piece piece, nextpiece;
        Tile matrix[ROWS][10];
        sf::Time ttm;
        std::vector<Effect> effects;
};

#endif // BOARD_HPP
