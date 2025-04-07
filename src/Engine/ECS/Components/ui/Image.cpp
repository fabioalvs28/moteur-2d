#include "pch.h"
#include "Image.h"

Image::Image(Entity* entity, Sprite* uiImage, sf::Vector2f position, sf::Vector2f scale )
: Component(entity), ScreenPosition(position), UIImage(uiImage), Scale(scale)
{
}

int Image::GetBitmask()
{
    return BITMASK;
}
