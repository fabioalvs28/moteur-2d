#pragma once

#include <SFML/Graphics/Sprite.hpp>

class Texture;

class Sprite : public sf::Sprite
{
public:
    Sprite(Texture& sprite);
    Sprite(sf::Sprite& sprite);
    ~Sprite();
    
    void SetAlpha(uint8_t alpha);
    Texture* GetTexture() const;

    Sprite* Cut(int x, int y, int width, int height);

private:
    Texture* mpTexture;
};
