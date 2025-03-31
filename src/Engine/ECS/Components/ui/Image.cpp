#include "pch.h"
#include "Image.h"

#include "Render/Texture.h"

Image::Image(Entity* entity, Sprite* sprite): Component(entity), mpTexture(sprite->GetTexture())
{
    UIImage = sprite;
}

int Image::GetBitmask()
{
    return BITMASK;
}

void Image::Serialize(json& json)
{
    json["UIImage"] = mpTexture->GetPath();
}

void Image::Deserialize(json& json)
{
    mpTexture = new Texture(json["UIImage"]);
    UIImage = new Sprite(*mpTexture);
}
