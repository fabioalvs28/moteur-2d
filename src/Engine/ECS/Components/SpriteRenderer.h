#pragma once

#include "Component.h"
#include "Render/Shader.h"
#include "Render/Sprite.h"

class SpriteRenderer : public Component
{

public:
    static constexpr int BITMASK = 1 << 2;
    
    SpriteRenderer(Entity* parent, Sprite* sprite, Shader* shader = nullptr);
    ~SpriteRenderer() override;
    int GetBitmask() override;
    void Serialize(json& json) override;
    void Deserialize(json& json) override;

    Sprite* Image;
    Shader* RendererShader;
};
