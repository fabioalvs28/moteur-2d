#pragma once

class Sprite;
class SpriteSheet;
class Resources
{
public:
    Resources() = default;
    ~Resources();
    
    void Initialize();
    void CreateShaders();
    void CreateParticles();
    void CreateTextures();
    void CreateSprite();
    void CreateFonts();
    void CreateSpriteSheet();
    
    static Resources& instance()
    {
        static Resources instance;
        return instance;
    }

    std::vector<Texture*> mTextures;
    std::vector<Sprite*> mSprites;
    ////////////////////////////////
    /////// SHADERS

    //Shader* DEFAULT_SHADER;
    
    ////////////////////////////////
    /////// TEXTURES

    Texture* DEFAULT_TEXTURE;
    Texture* SPRITE_SHEET;
    Texture* BAR_CONTAINER_TEXTURE;
    Texture* BAR_HEALTH_TEXTURE;
    Texture* BAR_EXP_TEXTURE;
    Texture* PETER_TEXTURE;
    Texture* EXP_TEXTURE;
    Texture* BUTTON_KONG_TEXTURE;
    
    Texture* WEAPON_BOOMERANG_TEXTURE;
    Texture* WEAPON_SWORD_TEXTURE;
    Texture* WEAPON_DEO_TEXTURE;
    Texture* WEAPON_LASER_TEXTURE;
    Texture* WEAPON_BOMB_TEXTURE;
    Texture* WEAPON_FABIOJR_TEXTURE;
    
    Texture* BUFF_KONG;
    Texture* BUFF_GC_ENGINE;
    Texture* BUFF_BODYCOUNT;
    Texture* BUFF_CARAMEL_BISCUIT;
    Texture* BUFF_KINDER;
    Texture* BUFF_DEV;

    //VFX
    Texture* SLASH_VFX_TEXTURE;
    
    Texture* ALEX_TEXTURE;
    ////////////////////////////////
    /////// SPRITES

    Sprite* KONG;
    Sprite* GC_ENGINE;
    Sprite* BODYCOUNT;
    Sprite* CARAMEL_BISCUIT;
    Sprite* KINDER;
    Sprite* DEV;

    Sprite* DEFAULT_SPRITE;
    Sprite* BAR_CONTAINER;
    Sprite* BAR_HEALTH;
    Sprite* BAR_EXP;
    Sprite* PETER;
    Sprite* EXP;
    Sprite* KONG_BUTTON;
    Sprite* SWORD;
    Sprite* BOMB;
    Sprite* FABIOJR;
    Sprite* DEO;
    Sprite* LASER;
    Sprite* BOOMERANG;
    //VFX
    Sprite* SLASH_VFX;

    Sprite* ALEX_SPRITE;
    ////////////////////////////////
    /////// FONTS

    sf::Font* DEFAULT_FONT;

    ////////////////////////////////
    /////// SPRITESHEETS
    SpriteSheet* VFX_SLASH;
};
