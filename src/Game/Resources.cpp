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
    WEAPON_BOOMERANG_TEXTURE = new Texture("Icones/Boomerang.png");
    WEAPON_SWORD_TEXTURE = new Texture("Icones/Sword.png");;
    WEAPON_DEO_TEXTURE = new Texture("Icones/Deo.png");;
    WEAPON_LASER_TEXTURE = new Texture("Icones/Laser.png");;
    WEAPON_BOMB_TEXTURE = new Texture("Icones/Bomb.png");;
    WEAPON_FABIOJR_TEXTURE = new Texture("Icones/Fabio JR.png");;
    SLASH_VFX_TEXTURE = new Texture("VFX/vfx-slash00.png");
    
    UI_SHEET_TEXTURE = new Texture("UI/SpriteSheet.png");
    BUTTON_KONG_TEXTURE = new Texture("ButtonKong.png");
    BUFF_DEV = new Texture("Icones/Dev++.png");
    BUFF_KONG = new Texture("Icones/Kong.png");
    BUFF_KINDER = new Texture("Icones/Kinder.png");
    BUFF_CARAMEL_BISCUIT = new Texture("Icones/CaramelBiscuit.png");
    BUFF_GC_ENGINE = new Texture("Icones/GC.png");
    BUFF_BODYCOUNT = new Texture("Icones/Bodycount.png");
}

void Resources::CreateSprite()
{
    DEFAULT_SPRITE = new Sprite(*DEFAULT_TEXTURE);
    BAR_CONTAINER = new Sprite(*BAR_CONTAINER_TEXTURE);
    BAR_HEALTH = new Sprite(*BAR_HEALTH_TEXTURE);
    BAR_EXP = new Sprite(*BAR_EXP_TEXTURE);
    PETER = new Sprite(*PETER_TEXTURE);
    EXP = new Sprite(*EXP_TEXTURE);
    SWORD = new Sprite(*WEAPON_SWORD_TEXTURE);
    BOMB = new Sprite(*WEAPON_BOMB_TEXTURE);
    FABIOJR = new Sprite(*WEAPON_FABIOJR_TEXTURE);
    DEO = new Sprite(*WEAPON_DEO_TEXTURE);
    LASER = new Sprite(*WEAPON_LASER_TEXTURE);
    BOOMERANG = new Sprite(*WEAPON_BOOMERANG_TEXTURE);
    ALEX_SPRITE = new Sprite(*ALEX_TEXTURE);
    KONG_BUTTON = new Sprite(*BUTTON_KONG_TEXTURE);
    KONG = new Sprite(*BUFF_KONG);
    DEV = new Sprite(*BUFF_DEV);
    CARAMEL_BISCUIT = new Sprite(*BUFF_CARAMEL_BISCUIT);
    BODYCOUNT = new Sprite(*BUFF_BODYCOUNT);
    GC_ENGINE = new Sprite(*BUFF_GC_ENGINE);
    KINDER = new Sprite(*BUFF_KINDER);
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
