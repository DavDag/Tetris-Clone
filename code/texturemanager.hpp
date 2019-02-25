#pragma once
#ifndef TEXTUREMANAGER_HPP
#define TEXTUREMANAGER_HPP

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

namespace Textures
{
    enum ID{    RedBlock, CyanBlock, BlueBlock, GreenBlock, PurpleBlock, YellowBlock, OrangeBlock,
                EmptyBlock, EmptyBlockDbg, BaseButton, EmptyButton, BackGround, BoardGround,
                MagicEffect1, MagicEffect2};
}

class TextureManager
{
    public:
        TextureManager();
        void loadTexture(const Textures::ID id, const std::string& filepath);
        const sf::Texture* get(const Textures::ID id) const;
    private:
        std::map<Textures::ID, sf::Texture*> textures;
};

extern TextureManager texturemanager;

#endif // TEXTUREMANAGER_HPP
