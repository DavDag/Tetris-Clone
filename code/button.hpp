#pragma once
#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>
#include <string>

class Button: public sf::Drawable, public sf::Transformable
{
    public:
        Button(sf::Vector2f dim, sf::Vector2f pos, const std::string& btext);
        bool contains(sf::Vector2f pos);
        void mark(bool marked);
        bool getMarked();
        void setText(std::string btext);
    private:
        virtual void draw(sf::RenderTarget& rt, sf::RenderStates rs) const;
        sf::Sprite sprite;
        sf::Vector2f origDim, currDim;
        sf::Text text;
        bool marked;
};

#endif // BUTTON_HPP
