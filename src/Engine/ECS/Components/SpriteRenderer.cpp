#include "pch.h"
#include "SpriteRenderer.h"

#include "Render/Texture.h"

SpriteRenderer::SpriteRenderer(Entity* parent, Sprite* sprite, Shader* shader)
: Component(parent), Image(sprite), RendererShader(shader)
{
    Image->setOrigin(parent->GetTransform()->position);
}


SpriteRenderer::~SpriteRenderer()
{
    if (texture)
        delete texture;
}

int SpriteRenderer::GetBitmask()
{
    return BITMASK;
}

void SpriteRenderer::Serialize(json& json)
{
    json["Texture"] = Image->GetTexture()->GetPath();
}

void SpriteRenderer::Deserialize(json& json)
{
    Image = nullptr;
    Texture* texture = new Texture(json["Texture"]);
    Image = new Sprite(*texture);
}
