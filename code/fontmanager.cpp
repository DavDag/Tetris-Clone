#include "fontmanager.hpp"

FontManager::FontManager()
{
    this->loadFont(Fonts::BaseFont,       "assets/fonts/base.ttf");
}

void FontManager::loadFont(const Fonts::ID id, const std::string& filepath)
{
    sf::Font* font = new(sf::Font);
    font->loadFromFile(filepath);
    this->fonts.insert({id, font});
}

const sf::Font* FontManager::get(const Fonts::ID id) const
{
    return this->fonts.find(id)->second;
}

FontManager fontmanager;
