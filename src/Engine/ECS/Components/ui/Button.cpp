﻿#include "pch.h"
#include "Button.h"

#include "Render/Colors.h"

Button::Button(Entity* entity, Sprite* sprite, sf::Vector2f position, sf::Vector2f scale, int width, int height, std::function<void()> buttonAction, std::function<void()> releaseAction):
    Component(entity),
    UIImage(sprite), CallBack(buttonAction), ReleaseCallback(releaseAction), ScreenPosition(position), Width(width), Height(height),
    IsClicked(false), IsReleased(true), Scale(scale)
{
    shape = new sf::RectangleShape({static_cast<float>(width), static_cast<float>(height)});
    shape->setFillColor(Colors::blue);
}

int Button::GetBitmask()
{
    return BITMASK;
}
