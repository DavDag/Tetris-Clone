#include "tile.hpp"

Tile::Tile(int x, int y, int w, int h):
sprite(),
x(x),
y(y),
marked(false),
color(Textures::EmptyBlock)
{
    this->sprite.setTexture(*texturemanager.get(Textures::EmptyBlock));
    this->sprite.scale(w / this->sprite.getGlobalBounds().width, h / this->sprite.getGlobalBounds().height);
    this->setPosition(this->x * w, this->y * h);
}

void Tile::setColor(Textures::ID id)
{
    this->sprite.setTexture(*texturemanager.get(id));
    this->color = id;
}

sf::FloatRect Tile::getBounds()
{
    return sf::FloatRect(sf::Vector2f(this->getPosition()), sf::Vector2f(44, 44));
}

bool Tile::getMarked()
{
    return this->marked;
}

Textures::ID Tile::getColor()
{
    return this->color;
}

void Tile::mark(bool marked)
{
    if(this->marked != marked)
    {
        this->marked = marked;
        if(DEBUG)
        {
            if(marked)
            {
                this->sprite.setColor(sf::Color::Yellow);
            }
            else
            {
                this->sprite.setColor(sf::Color::White);
            }
        }
    }
}

bool Tile::isEmpty()
{
    return this->color == Textures::EmptyBlock || this->color == Textures::EmptyBlockDbg;
}

void Tile::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
{
    rs.transform *= this->getTransform();
    rs.texture = NULL;
    rt.draw(this->sprite, rs);
}
