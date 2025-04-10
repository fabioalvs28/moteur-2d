﻿#pragma once

#include "ECS/Components/Component.h"

class Sprite;

class Image : public Component
{
public:
    static constexpr int BITMASK = 1 << 16;
    
    Image(Entity* entity, Sprite* uiImage = nullptr, sf::Vector2f position = {0.0f, 0.0f}, sf::Vector2f scale = {1.0f, 1.0f});
    ~Image() override = default;
    int GetBitmask() override;

    sf::Vector2f ScreenPosition;
    sf::Vector2f Scale;
    Sprite* UIImage;

    void Serialize(json& json) override {}
    void Deserialize(json& json) override {}
};
