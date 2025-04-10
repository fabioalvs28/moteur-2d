#include "pch.h"
#include "Text.h"

Text::Text(Entity* entity, sf::Font* font, int size, std::string text, sf::Vector2f position)
: Component(entity)
{
    WriteText = new sf::Text(*font);
    ScreenPosition = position;
    WriteText->setString(text);
    WriteText->setCharacterSize(size);
    WriteText->setFillColor(sf::Color::Black);
}

int Text::GetBitmask()
{
    return BITMASK;
}
