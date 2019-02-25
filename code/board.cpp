#include "board.hpp"
#include "gamestatestart.hpp"

Board::Board(GameStateStart* game):
effects(0)
{
    this->game = game;
    this->nextpiece = Piece((Pieces::ID) (rand() % 7), (Textures::ID) (rand() % 7));
    this->ttm = sf::milliseconds(0);
    this->bg.setSize(sf::Vector2f(440, ROWS * 44));
    this->bg.setFillColor(sf::Color::Transparent);
    this->bg.setOutlineThickness(3.f);
    this->bg.setOutlineColor(sf::Color(128, 128, 128));
    this->setPosition(20, 14);
    this->createPiece();
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            this->matrix[i][j] = Tile(j, i, 44, 44);
            if(DEBUG)
            {
                this->matrix[i][j].setColor(Textures::EmptyBlockDbg);
            }
        }
    }
}

int Board::eraseLines()
{
    int tot = 0;
    for(int i = 0; i < ROWS; i++)
    {
        bool found = true;
        for(int j = 0; j < 10; j++)
        {
            if(this->matrix[i][j].isEmpty())
            {
                found = false;
                break;
            }
        }
        if(found)
        {
            tot++;
            for(int j = 0; j < 10; j++)
            {
                this->matrix[i][j].setColor((DEBUG) ? Textures::EmptyBlockDbg : Textures::EmptyBlock);
                this->effects.push_back(Effect(this->matrix[i][j].getPosition()));
            }
            for(int k = i; k > 0; k--)
            {
                for(int j = 0; j < 10; j++)
                {
                    this->matrix[k][j].setColor(this->matrix[k-1][j].getColor());
                }
            }
        }
    }
    return tot;
}

void Board::createPiece()
{
    this->piece = Piece(this->nextpiece.getType(), this->nextpiece.getColor());
    this->nextpiece = Piece((Pieces::ID) (rand() % 7), (Textures::ID) (rand() % 7));
    this->nextpiece.move(550, 10);
    this->piece.move(220, -this->piece.getBounds().height);
}

void Board::update(sf::Time dt, int diff)
{
    for(int i = this->effects.size() - 1; i >= 0; i--)
    {
        this->effects[i].update(dt);
        if(this->effects[i].getEnded())
        {
            this->effects.erase(this->effects.begin() + i);
        }
    }
    this->ttm += dt;
    if(this->ttm.asMilliseconds() > (10 - diff) * 50)
    {
        this->ttm = sf::milliseconds(0);
        this->piece.move(0, 44);
        if(this->checkCollision())
        {
            this->piece.move(0, -44);
            if(this->piece.getBounds().top <= 0)
            {
                this->game->restart();
            }
            else
            {
                this->place(this->piece.getColor());
                this->createPiece();
                this->game->placed();
            }
        }
    }
    if(this->piece.getBounds().top + this->piece.getBounds().height > ROWS * 44)
    {
        this->piece.move(0, -44);
        this->place(this->piece.getColor());
        this->createPiece();
        this->game->placed();
    }
    this->collide();
}

void Board::place(Textures::ID color)
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(this->matrix[i][j].getMarked())
            {
                this->matrix[i][j].setColor(color);
            }
        }
    }
}

bool Board::checkCollision()
{
    std::vector<Tile> tiles(this->piece.getTiles());
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            if(this->matrix[i][j].isEmpty()) continue;
            for(Tile& t: tiles)
            {
                sf::FloatRect trect = t.getBounds();
                trect.top += this->piece.getPosition().y;
                trect.left += this->piece.getPosition().x;
                if(trect.intersects(this->matrix[i][j].getBounds()))
                {
                    return true;
                }
            }
        }
    }
    return false;
}

void Board::collide()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            this->matrix[i][j].mark(false);
            if(this->piece.check(this->matrix[i][j].getBounds()))
            {
                this->matrix[i][j].mark(true);
            }
        }
    }
}

void Board::movePiece(Directions::ID dir)
{
    if(this->game->paused)
    {
        return;
    }
    switch(dir)
    {
        case Directions::Left:
        {
            if(this->piece.getBounds().left > 22)
            {
                this->piece.move(-44, 0);
                if(this->checkCollision())
                {
                    this->piece.move(44, 0);
                }
            }
            break;
        }
        case Directions::Right:
        {
            if(this->piece.getBounds().left  + this->piece.getBounds().width < 418)
            {
                this->piece.move(44, 0);
                if(this->checkCollision())
                {
                    this->piece.move(-44, 0);
                }
            }
            break;
        }
        case Directions::Down:
        {
            if(this->piece.getBounds().top + this->piece.getBounds().height < ROWS * 44 - 22)
            {
                this->piece.move(0, 44);
                if(this->checkCollision())
                {
                    this->piece.move(0, -44);
                }
            }
            break;
        }
        default:
        {
            break;
        }
    }
}

void Board::rotatePiece()
{
    sf::Vector2f pos = this->piece.getPosition();
    this->piece.rotate();
    if(this->piece.getBounds().left + this->piece.getBounds().width > 440)
    {
        this->piece.move(-44, 0);
        if(this->piece.getBounds().left + this->piece.getBounds().width > 440)
        {
            this->piece.move(-44, 0);
        }
    }
    else if(this->piece.getBounds().left < 0)
    {
        this->piece.move(44, 0);
        if(this->piece.getBounds().left < 0)
        {
            this->piece.move(44, 0);
        }
    }
    if(this->checkCollision())
    {
        this->piece.setPosition(pos);
        for(int i = 0; i < 3; i++)
        {
            this->piece.rotate();
        }
    }
}

void Board::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
{
    rs.transform *= this->getTransform();
    rs.texture = NULL;
    rt.draw(this->bg, rs);
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < 10; j++)
        {
            rt.draw(this->matrix[i][j], rs);
        }
    }
    rt.draw(this->piece, rs);
    rt.draw(this->nextpiece, rs);
    for(unsigned int i = 0; i < this->effects.size(); i++)
    {
        rt.draw(this->effects[i], rs);
    }
}
