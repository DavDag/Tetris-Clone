#include "button.hpp"
#include "texturemanager.hpp"
#include "fontmanager.hpp"

Button::Button(sf::Vector2f dim, sf::Vector2f pos, const std::string& btext):
origDim(0.f, 0.f),
currDim(dim.x, dim.y),
marked(false)
{
    this->sprite.setTexture(*texturemanager.get(Textures::EmptyButton));
    this->origDim = sf::Vector2f(this->sprite.getGlobalBounds().width, this->sprite.getGlobalBounds().height);
    this->sprite.setOrigin(this->origDim.x / 2, this->origDim.y / 2);
    this->sprite.scale(dim.x / this->origDim.x, dim.y / this->origDim.y);

    this->text.setFont(*fontmanager.get(Fonts::BaseFont));
    this->text.setFillColor(sf::Color::White);
    this->text.setString(btext);
    this->text.setCharacterSize(dim.x / (btext.size() + 1));
    this->text.setOrigin(this->text.getGlobalBounds().width / 2, this->text.getGlobalBounds().height / 2);

    this->setPosition(pos);
}

void Button::setText(std::string btext)
{
    this->text.setString(btext);
    this->text.setCharacterSize(this->currDim.x / (btext.size() + 1));
}

bool Button::contains(sf::Vector2f pos)
{
    sf::FloatRect rect = this->sprite.getGlobalBounds();
    rect.width *= this->getScale().x;
    rect.height *= this->getScale().y;
    rect.left = this->getPosition().x - rect.width / 2;
    rect.top = this->getPosition().y - rect.height / 2;
    return rect.contains(pos);
}

void Button::mark(bool marked)
{
    if(this->marked != marked)
    {
        this->marked = marked;
        if(marked)
        {
            this->setScale(1.5f, 1.5f);
        }
        else
        {
            this->setScale(1.f, 1.f);
        }
    }
}

bool Button::getMarked()
{
    return this->marked;
}

void Button::draw(sf::RenderTarget& rt, sf::RenderStates rs) const
{
    rs.transform *= this->getTransform();
    rs.texture = NULL;
    rt.draw(this->sprite, rs);
    rt.draw(this->text, rs);
}
