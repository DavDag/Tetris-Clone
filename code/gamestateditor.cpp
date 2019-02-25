#include "gamestateditor.hpp"
#include "gamestatestart.hpp"

GameStateEditor::GameStateEditor(Game* game):
Bplay(sf::Vector2f(200, 75), sf::Vector2f(400, 250), "Play"),
Bsettings(sf::Vector2f(200, 75), sf::Vector2f(400, 350), "Settings")
{
    this->game = game;
}

void GameStateEditor::draw()
{
    this->game->window.draw(this->Bplay);
    this->game->window.draw(this->Bsettings);
}

void GameStateEditor::update(sf::Time dt)
{

}

void GameStateEditor::handleInput()
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
                    case sf::Keyboard::Escape:
                    {
                        this->game->window.close();
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
                if(this->Bplay.contains(pos))
                {
                    this->Bplay.mark(true);
                    this->Bsettings.mark(false);
                }
                else if(this->Bsettings.contains(pos))
                {
                    this->Bplay.mark(false);
                    this->Bsettings.mark(true);
                }
                else
                {
                    this->Bplay.mark(false);
                    this->Bsettings.mark(false);
                }
                break;
            }
            case sf::Event::MouseButtonPressed:
            {
                if(this->Bsettings.getMarked())
                {

                }
                else if(this->Bplay.getMarked())
                {
                    this->game->pushState(new GameStateStart(this->game));
                    this->Bplay.mark(false);
                    this->Bsettings.mark(false);
                    if(DEBUG)
                    {
                        printf("State added\n");
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

std::string GameStateEditor::getName()
{
    return "GameStateEditor";
}
