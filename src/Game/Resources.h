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

    //VFX
    Texture* SLASH_VFX_TEXTURE;
    
    Texture* ALEX_TEXTURE;
    ////////////////////////////////
    /////// SPRITES

    Sprite* DEFAULT_SPRITE;
    Sprite* BAR_CONTAINER;
    Sprite* BAR_HEALTH;
    Sprite* BAR_EXP;
    Sprite* PETER;
    Sprite* EXP;

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
