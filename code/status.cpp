#include "status.hpp"
#include "gamestatestart.hpp"
#include "fontmanager.hpp"

Status::Status(GameStateStart* game):
score(),
line(),
level(),
pscore(0),
pline(0),
plevel(1)
{
    this->game = game;
    this->bg.setSize(sf::Vector2f(300, 200));
    this->bg.setFillColor(sf::Color::Transparent);
    this->bg.setOutlineThickness(3.f);
    this->bg.setOutlineColor(sf::Color(128, 128, 128));
    this->setPosition(sf::Vector2f(480, 20));
    this->line.setFont(*fontmanager.get(Fonts::BaseFont));
    this->line.setString("Line:  0");
    this->line.setCharacterSize(20);
    this->line.setFillColor(sf::Color::White);
    this->line.setPosition(20, 275);
    this->level.setFont(*fontmanager.get(Fonts::BaseFont));
    this->level.setString("Level: 1");
    this->level.setCharacterSize(20);
    this->level.setFillColor(sf::Color::White);
    this->level.setPosition(20, 350);
    this->score.setFont(*fontmanager.get(Fonts::BaseFont));
    this->score.setString("Score: 0");
    this->score.setCharacterSize(20);
    this->score.setFillColor(sf::Color::White);
    this->score.setPosition(20, 425);
}

void Status::addScore(int increment)
{
    this->pscore += increment;
    this->score.setString("Score: " + std::to_string(this->pscore));
}

void Status::addLevel(int increment)
{
    this->plevel += increment;
    this->level.setString("Level: " + std::to_string(this->plevel));
}

int Status::getLevel()
{
    return this->plevel;
}

void Status::addLine(int increment)
{
    if(((this->pline + increment) / 10) > (this->pline / 10))
    {
        this->addLevel(1);
    }
    this->pline += increment;
    this->line.setString("Line: " + std::to_string(this->pline));
}

void Status::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
{
    rs.transform *= this->getTransform();
    rs.texture = NULL;
    rt.draw(this->bg, rs);
    rt.draw(this->score, rs);
    rt.draw(this->line, rs);
    rt.draw(this->level, rs);
}
