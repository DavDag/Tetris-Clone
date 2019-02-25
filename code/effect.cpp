#include "effect.hpp"

#include "texturemanager.hpp"

Effect::Effect(sf::Vector2f pos):
ended(false)
{
    this->setPosition(pos);
    int n = rand() % 3 + 3;
    for(int i = 0; i < n; i++)
    {
        this->t.push_back(sf::Time());
        this->t[i] = sf::milliseconds(0);
        this->tmax.push_back(sf::Time());
        this->tmax[i] = sf::milliseconds(250 + rand() % 500);
        this->sprites.push_back(sf::Sprite());
        this->sprites[i].setTexture(*texturemanager.get((rand() % 2 == 0) ? Textures::MagicEffect1 : Textures::MagicEffect2));
        this->sprites[i].setPosition(rand() % 44, rand() % 44);
    }
}

void Effect::update(sf::Time dt)
{
    this->ended = true;
    for(unsigned int i = 0; i < this->t.size(); i++)
    {
        this->t[i] += dt;
        int ratio = this->t[i].asSeconds() / (this->tmax[i].asSeconds() / 10.f);
        this->sprites[i].setTextureRect(sf::IntRect(0, 32 * ratio, 32, 32));
        if(this->t[i].asMilliseconds() < this->tmax[i].asMilliseconds())
        {
            this->ended = false;
        }
    }
}

bool Effect::getEnded()
{
    return this->ended;
}

void Effect::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
{
    rs.transform *= this->getTransform();
    rs.texture = NULL;
    for(unsigned int i = 0; i < this->sprites.size(); i++)
    {
        rt.draw(this->sprites[i], rs);
    }
}
