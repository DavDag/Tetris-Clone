#include "texturemanager.hpp"

TextureManager::TextureManager()
{
    this->loadTexture(Textures::RedBlock,       "assets/tiles/red.png");
    this->loadTexture(Textures::CyanBlock,      "assets/tiles/cyan.png");
    this->loadTexture(Textures::OrangeBlock,    "assets/tiles/arancione.png");
    this->loadTexture(Textures::BlueBlock,      "assets/tiles/blu.png");
    this->loadTexture(Textures::YellowBlock,    "assets/tiles/giallo.png");
    this->loadTexture(Textures::GreenBlock,     "assets/tiles/verde.png");
    this->loadTexture(Textures::PurpleBlock,    "assets/tiles/porpora.png");
    this->loadTexture(Textures::EmptyBlock,     "assets/tiles/empty.png");
    this->loadTexture(Textures::EmptyBlockDbg,  "assets/tiles/emptydbg.png");
    this->loadTexture(Textures::BaseButton,     "assets/gui/button.png");
    this->loadTexture(Textures::EmptyButton,    "assets/gui/emptybutton.png");
    this->loadTexture(Textures::BackGround,     "assets/gui/bg.png");
    this->loadTexture(Textures::BoardGround,    "assets/gui/board2.png");
    this->loadTexture(Textures::MagicEffect1,   "assets/gui/magic_effect.png");
    this->loadTexture(Textures::MagicEffect2,   "assets/gui/magic_effect_2.png");
}

void TextureManager::loadTexture(const Textures::ID id, const std::string& filepath)
{
    sf::Texture* texture = new(sf::Texture);
    texture->loadFromFile(filepath);
    this->textures.insert({id, texture});
}

const sf::Texture* TextureManager::get(const Textures::ID id) const
{
    return this->textures.find(id)->second;
}

TextureManager texturemanager;
