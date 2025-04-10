#pragma once
#include <functional>

#include "ECS/Components/Component.h"

class Sprite;

class Button : public Component
{
public:
    static constexpr int BITMASK = 1 << 17;
    
    Button(Entity* entity, Sprite* uiImage = nullptr, sf::Vector2f position = {0.0f, 0.0f}, sf::Vector2f scale = { 1.0f, 1.0f }, int width = 50, int height = 50, std::function<void()> buttonAction = nullptr, std::function<void()> releaseAction = nullptr);
    ~Button() override = default;
    int GetBitmask() override;

    Sprite* UIImage;
    sf::Vector2f ScreenPosition;
    int Width;
    int Height;
    sf::Vector2f Scale;
    bool IsClicked;
    bool IsReleased;

    sf::RectangleShape* shape;

   std::function<void()> CallBack;
   std::function<void()> ReleaseCallback;

    void Serialize(json& json) override {};
    void Deserialize(json& json) override {};
};
