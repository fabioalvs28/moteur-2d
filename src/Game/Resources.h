#pragma once

class Sprite;

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
    
    static Resources& instance()
    {
        static Resources instance;
        return instance;
    }

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
    
    ////////////////////////////////
    /////// SPRITES

    Sprite* DEFAULT_SPRITE;
    Sprite* BAR_CONTAINER;
    Sprite* BAR_HEALTH;
    Sprite* BAR_EXP;

    ////////////////////////////////
    /////// FONTS

    sf::Font* DEFAULT_FONT;
};
