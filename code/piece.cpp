#include "piece.hpp"

Piece::Piece(Pieces::ID type, Textures::ID color):
tiles(),
type(type),
color(color)
{
    switch(type)
    {
        case Pieces::I:
        {
            this->tiles.push_back(Tile(1, 0, 44, 44));
            this->tiles.push_back(Tile(1, 1, 44, 44));
            this->tiles.push_back(Tile(1, 2, 44, 44));
            this->tiles.push_back(Tile(1, 3, 44, 44));
            break;
        }
        case Pieces::O:
        {
            this->tiles.push_back(Tile(1, 1, 44, 44));
            this->tiles.push_back(Tile(2, 1, 44, 44));
            this->tiles.push_back(Tile(1, 2, 44, 44));
            this->tiles.push_back(Tile(2, 2, 44, 44));
            break;
        }
        case Pieces::J:
        {
            this->tiles.push_back(Tile(1, 1, 44, 44));
            this->tiles.push_back(Tile(1, 2, 44, 44));
            this->tiles.push_back(Tile(1, 3, 44, 44));
            this->tiles.push_back(Tile(0, 3, 44, 44));
            break;
        }
        case Pieces::L:
        {
            this->tiles.push_back(Tile(0, 1, 44, 44));
            this->tiles.push_back(Tile(1, 1, 44, 44));
            this->tiles.push_back(Tile(1, 2, 44, 44));
            this->tiles.push_back(Tile(1, 3, 44, 44));
            break;
        }
        case Pieces::S:
        {
            this->tiles.push_back(Tile(1, 1, 44, 44));
            this->tiles.push_back(Tile(1, 2, 44, 44));
            this->tiles.push_back(Tile(0, 2, 44, 44));
            this->tiles.push_back(Tile(0, 3, 44, 44));
            break;
        }
        case Pieces::Z:
        {
            this->tiles.push_back(Tile(0, 1, 44, 44));
            this->tiles.push_back(Tile(0, 2, 44, 44));
            this->tiles.push_back(Tile(1, 2, 44, 44));
            this->tiles.push_back(Tile(1, 3, 44, 44));
            break;
        }
        case Pieces::T:
        {
            this->tiles.push_back(Tile(1, 1, 44, 44));
            this->tiles.push_back(Tile(1, 2, 44, 44));
            this->tiles.push_back(Tile(0, 2, 44, 44));
            this->tiles.push_back(Tile(1, 3, 44, 44));
            break;
        }
        default:
        {
            break;
        }
    }
    for(auto& t: tiles)
    {
        t.setColor(color);
    }
}

sf::FloatRect Piece::getBounds() const
{
    int xmax = 0, ymax = 0, xmin = 10, ymin = 10;
    for(Tile t: this->tiles)
    {
        xmax = std::max(xmax, t.x);
        ymax = std::max(ymax, t.y);
        xmin = std::min(xmin, t.x);
        ymin = std::min(ymin, t.y);
    }
    xmax++;
    ymax++;
    return sf::FloatRect(this->getPosition() + sf::Vector2f(xmin * 44, ymin * 44), sf::Vector2f((xmax - xmin) * 44, (ymax - ymin) * 44));
}

Textures::ID Piece::getColor()
{
    return this->color;
}

std::vector<Tile>& Piece::getTiles()
{
    return this->tiles;
}

bool Piece::check(sf::FloatRect rect)
{
    for(Tile& t: this->tiles)
    {
        sf::FloatRect inter, trect = t.getBounds();
        trect.top += this->getPosition().y;
        trect.left += this->getPosition().x;
        if(trect.intersects(rect, inter))
        {
            if(inter.height > 22)
            {
                return true;
            }
        }
    }
    return false;
}

void Piece::rotate()
{
    if(this->type == Pieces::O)
    {
        return;
    }
    int cx = this->tiles[1].x, cy = this->tiles[1].y;
    for(Tile& t: this->tiles)
    {
        int x = t.y - cy, y = t.x - cx;
        t.x = cx - x, t.y = cy + y;
        t.setPosition(t.x * 44, t.y * 44);
    }
}

Pieces::ID Piece::getType()
{
    return this->type;
}

void Piece::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
{
    rs.transform *= this->getTransform();
    rs.texture = NULL;
    for(auto& t: tiles)
    {
        rt.draw(t, rs);
    }
    if(DEBUG)
    {
        sf::RectangleShape rect(sf::Vector2f(this->getBounds().width, this->getBounds().height));
        rect.setPosition(this->getBounds().left, this->getBounds().top);
        rect.move(-this->getPosition());
        rect.setFillColor(sf::Color::Transparent);
        rect.setOutlineColor(sf::Color::Green);
        rect.setOutlineThickness(4.f);
        rt.draw(rect, rs);
    }
}
