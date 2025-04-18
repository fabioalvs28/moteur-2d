﻿#include "SpriteSheet.h"

#include "Sprite.h"
#include "Texture.h"

SpriteSheet::SpriteSheet(Texture& spriteSheet) : Sprite(spriteSheet), SpriteCount(0)
{
    setTexture(spriteSheet);
}

void SpriteSheet::Extract(int startX, int startY, int singleWidth, int singleHeight, int width, int height)
{

    m_size.x = singleWidth;
    m_size.y = singleHeight;

    m_totalSize.x = width;
    m_totalSize.y = height;
    for (int x = startX; x < startX + width; x += singleWidth)
    {
        for (int y = startY; y < startY + height; y += singleHeight)
        {
            sprites.emplace_back(x, y);
            SpriteCount++;
        }
    }

}

sf::Vector2i SpriteSheet::GetSpriteSheetPart(int index)
{
    return sprites[index];
}

void SpriteSheet::SetSpriteAt(sf::Vector2i offset, sf::Vector2i size)
{
    setTextureRect({ offset, size });
}

void SpriteSheet::SetSprite(int index)
{
    setTextureRect({ sprites[index], m_size });
}

sf::Vector2i SpriteSheet::GetSize()
{
    return m_size;
}

sf::Vector2i SpriteSheet::GetTotalSize()
{
    return m_totalSize;
}

Texture* SpriteSheet::GetTexture()
{
    return m_pTexture;
}

sf::Sprite SpriteSheet::CreateSpriteAt(sf::Vector2i offset, sf::Vector2i size)
{
    sf::Sprite pSprite(getTexture(), {offset, size});
    return pSprite;
}