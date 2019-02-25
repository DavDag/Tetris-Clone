#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <iostream>

#include "game.hpp"
#include "gamestate.hpp"
#include "texturemanager.hpp"
#include "board.hpp"

Game::Game():
bg()
{
    this->window.create(sf::VideoMode(600, 600), "Tetris Clone by Davide Risaliti", sf::Style::Close);
    this->view.setSize(sf::Vector2f(800, ROWS * 44 + 28));
    this->view.setCenter(400, ROWS * 22 + 11);
    this->window.setFramerateLimit(240);
    this->window.setKeyRepeatEnabled(false);
    this->bg.setTexture(*texturemanager.get(Textures::BackGround));
    this->bg.setScale(800.f / this->bg.getGlobalBounds().width, (ROWS * 44 + 28) / this->bg.getGlobalBounds().height);
}

Game::~Game()
{
    while(!this->states.empty())
    {
        this->popState();
    }
}

void Game::pushState(GameState* state)
{
    this->states.push(state);
}

void Game::popState()
{
    this->states.pop();
}

void Game::changeState(GameState* state)
{
    if(!this->states.empty())
    {
        this->popState();
    }
    pushState(state);
}

GameState* Game::peekState()
{
    if(this->states.empty())
    {
        return nullptr;
    }
    return this->states.top();
}

int Game::getSize()
{
    return this->states.size();
}

void Game::gameLoop()
{
    sf::Clock clock;

    while(this->window.isOpen())
    {
        sf::Time dt = clock.restart();
        if(this->peekState() == nullptr)
        {
            continue;
        }

        if(DEBUG)
        {
            std::stack<GameState*> s(this->states);
            while(!s.empty())
            {
                std::cout << s.top()->getName() << " ";
                s.pop();
            }
            std::cout << "\n";
        }
        GameState* gs = this->peekState();
        gs->handleInput();
        gs->update(dt);
        this->window.clear(sf::Color::Black);
        this->window.draw(this->bg);
        this->window.setView(this->view);
        gs->draw();
        this->window.display();
    }
}
