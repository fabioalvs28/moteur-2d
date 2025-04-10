#include "pch.h"
#include "Resources.h"

#include "Render/Sprite.h"
#include "Render/Texture.h"
#include "Render/SpriteSheet.h"

Resources::~Resources()
{
}

void Resources::Initialize()
{
    Resources* resources = &instance();
    
    resources->CreateShaders();
    resources->CreateParticles();
    resources->CreateTextures();
    resources->CreateSprite();
    resources->CreateFonts();
    resources->CreateSpriteSheet();
}

void Resources::CreateShaders()
{
    //DEFAULT_SHADER = new Shader("shaderPath", Shader::Type::Vertex);
}

void Resources::CreateParticles()
{
}

void Resources::CreateTextures()
{
    DEFAULT_TEXTURE = new Texture("perso.png");
    PETER_TEXTURE = new Texture("Peter.png");
    BAR_CONTAINER_TEXTURE = new Texture("UI/gui_emptybar.png");
    BAR_HEALTH_TEXTURE = new Texture("UI/gui_HPBar.png");
    BAR_EXP_TEXTURE = new Texture("UI/gui_MPBar.png");
    EXP_TEXTURE = new Texture("UI/gui_lightIcon.png");
    SPRITE_SHEET = new Texture("../../res/Tiles/tileset.png", false);
    ALEX_TEXTURE = new Texture("AlexLeMechant.png");

    SLASH_VFX_TEXTURE = new Texture("VFX/vfx-slash00.png");
    
    UI_SHEET_TEXTURE = new Texture("UI/SpriteSheet.png");
}

void Resources::CreateSprite()
{
    DEFAULT_SPRITE = new Sprite(*DEFAULT_TEXTURE);
    BAR_CONTAINER = new Sprite(*BAR_CONTAINER_TEXTURE);
    BAR_HEALTH = new Sprite(*BAR_HEALTH_TEXTURE);
    BAR_EXP = new Sprite(*BAR_EXP_TEXTURE);
    PETER = new Sprite(*PETER_TEXTURE);
    EXP = new Sprite(*EXP_TEXTURE);

    ALEX_SPRITE = new Sprite(*ALEX_TEXTURE);

}

void Resources::CreateFonts()
{
    DEFAULT_FONT = new sf::Font("../../res/Fonts/alagard.ttf");
}

void Resources::CreateSpriteSheet()
{
    VFX_SLASH = new SpriteSheet(*SLASH_VFX_TEXTURE);
    VFX_SLASH->Extract(0, 0, 128, 128, 512, 128);
    //VFX_SLASH->setOrigin(sf::Vector2f(SLASH_VFX_TEXTURE->getSize().x / 2, SLASH_VFX_TEXTURE->getSize().y / 2));
    UI_SHEET = new SpriteSheet(*UI_SHEET_TEXTURE);
}
