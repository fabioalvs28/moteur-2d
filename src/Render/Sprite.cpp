#include "Sprite.h"

#include "Texture.h"

Sprite::Sprite(Texture& texture) : sf::Sprite(texture), mpTexture(&texture)
{
}

Sprite::Sprite(sf::Sprite& sprite) : sf::Sprite(sprite), mpTexture()
{
}

Sprite::~Sprite()
{
    delete mpTexture;
}

void Sprite::SetAlpha(uint8_t alpha)
{
    sf::Color color = getColor();
    color.a = alpha;
    setColor(color);
}

Texture* Sprite::GetTexture() const
{
    return mpTexture;
}

Sprite* Sprite::Cut(int x, int y, int width, int height)
{
    Sprite* part = new Sprite(*this);
    part->setTextureRect(sf::IntRect({x,y}, {width,height}));
    part->scale({1.0f, 1.0f});
    return part;
}