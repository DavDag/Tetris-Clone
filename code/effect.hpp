#pragma once
#ifndef EFFECT_HPP
#define EFFECT_HPP

#include <SFML/Graphics.hpp>

class Effect: public sf::Drawable, public sf::Transformable
{
    public:
        Effect(){}
        Effect(sf::Vector2f pos);
        bool getEnded();
        void update(sf::Time dt);
    private:
        virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;
        bool ended;
        std::vector<sf::Sprite> sprites;
        std::vector<sf::Time> t, tmax;
};

#endif // EFFECT_HPP
