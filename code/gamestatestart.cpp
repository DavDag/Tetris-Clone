#include "gamestatestart.hpp"
#include "fontmanager.hpp"

GameStateStart::GameStateStart(Game* game):
Bback(sf::Vector2f(125, 50), sf::Vector2f(640, 550), "Back"),
Bpause(sf::Vector2f(125, 50), sf::Vector2f(640, 625), "Pause"),
status(this),
board(this),
paused(false),
ended(false)
{
    this->game = game;
    this->msg.setFont(*fontmanager.get(Fonts::BaseFont));
    this->msg.setCharacterSize(32);
    this->msg.setString("");
    this->msg.setPosition(150, ROWS * 22 + 14);
}

void GameStateStart::draw()
{
    this->game->window.draw(this->Bback);
    this->game->window.draw(this->Bpause);
    this->game->window.draw(this->status);
    this->game->window.draw(this->board);
    this->game->window.draw(this->msg);
}

void GameStateStart::placed()
{
    this->status.addScore(30);
}

void GameStateStart::update(sf::Time dt)
{
    if(this->paused || this->ended)
    {
        return;
    }
    this->board.update(dt, this->status.getLevel());
    int tot = this->board.eraseLines();
    if(tot > 0)
    {
        this->status.addLine(tot);
        this->status.addScore(100 + (1 << tot) * 100);
    }
}

void GameStateStart::handleInput()
{
    sf::Event event;
    while(this->game->window.pollEvent(event))
    {
        switch(event.type)
        {
            case sf::Event::Closed:
            {
                this->game->window.close();
                break;
            }
            case sf::Event::KeyPressed:
            {
                switch(event.key.code)
                {
                    case sf::Keyboard::A:
                    case sf::Keyboard::Left:
                    {
                        this->board.movePiece(Directions::Left);
                        break;
                    }
                    case sf::Keyboard::D:
                    case sf::Keyboard::Right:
                    {
                        this->board.movePiece(Directions::Right);
                        break;
                    }
                    case sf::Keyboard::S:
                    case sf::Keyboard::Down:
                    {
                        this->board.movePiece(Directions::Down);
                        break;
                    }
                    case sf::Keyboard::W:
                    case sf::Keyboard::Up:
                    case sf::Keyboard::Space:
                    {
                        this->board.rotatePiece();
                        break;
                    }
                    case sf::Keyboard::Escape:
                    {
                        this->paused = !this->paused;
                        if(this->paused)
                        {
                            this->msg.setString("PAUSED");
                        }
                        else
                        {
                            this->msg.setString("");
                        }
                        break;
                    }
                    default:
                    {
                        break;
                    }
                }
                break;
            }
            case sf::Event::MouseMoved:
            {
                sf::Vector2f pos = this->game->window.mapPixelToCoords(sf::Mouse::getPosition(this->game->window));
                if(this->Bback.contains(pos))
                {
                    this->Bback.mark(true);
                    this->Bpause.mark(false);
                }
                else if(this->Bpause.contains(pos))
                {
                    this->Bback.mark(false);
                    this->Bpause.mark(true);
                }
                else
                {
                    this->Bback.mark(false);
                    this->Bpause.mark(false);
                }
                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                if(this->Bback.getMarked())
                {
                    this->game->popState();
                }
                else if(this->Bpause.getMarked())
                {
                    if(this->ended)
                    {
                        this->game->changeState(new GameStateStart(this->game));
                    }
                    this->paused = !this->paused;
                    if(this->paused)
                    {
                        this->msg.setString("PAUSED");
                    }
                    else
                    {
                        this->msg.setString("");
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
}

void GameStateStart::restart()
{
    this->msg.setString("You Lose");
    this->ended = true;
    this->Bpause.setText("Reset");
}

std::string GameStateStart::getName()
{
    return "GameStateStart";
}
