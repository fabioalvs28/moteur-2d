﻿#include "pch.h"
#include "ProgressBar.h"

ProgressBar::ProgressBar(Entity* entity, Sprite* background, Sprite* progressBar, sf::Vector2f position, sf::Vector2f barOffset) :
    Component(entity), BackgroundImage(background), Bar(progressBar), ScreenPosition(position), BarOffset(barOffset),
    Progress(0),
    Maximum(100),
    Scale({1.0f,1.0f})
{
}

int ProgressBar::GetBitmask()
{
    return BITMASK;
}
