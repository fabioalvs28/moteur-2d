#pragma once
#include "ECS/Components/Component.h"
#include "Render/Sprite.h"

class Image : public Component
{
public:
    static constexpr int BITMASK = 1 << 7;
    
    Image(Entity* entity, Sprite* uiImage);
    ~Image() override = default;
    int GetBitmask() override;

    void Serialize(json& json) override;
    void Deserialize(json& json) override;
    Sprite* UIImage;

private:
    Texture* mpTexture;
};
