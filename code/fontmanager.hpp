#pragma once
#ifndef FONTMANAGER_HPP
#define FONTMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

namespace Fonts
{
    enum ID{BaseFont};
}

class FontManager
{
    public:
        FontManager();
        void loadFont(const Fonts::ID id, const std::string& filepath);
        const sf::Font* get(const Fonts::ID id) const;
    private:
        std::map<Fonts::ID, sf::Font*> fonts;
};

extern FontManager fontmanager;

#endif // FONTMANAGER_HPP

