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

    std::vector<Texture*> mTextures;
    std::vector<Sprite*> mSprites;
    ////////////////////////////////
    /////// SHADERS

    //Shader* DEFAULT_SHADER;
    
    ////////////////////////////////
    /////// TEXTURES

    Texture* DEFAULT_TEXTURE;
    Texture* SPRITE_SHEET;
    Texture* ALEX_TEXTURE;
    ////////////////////////////////
    /////// SPRITES

    Sprite* DEFAULT_SPRITE;
    Sprite* ALEX_SPRITE;
    ////////////////////////////////
    /////// FONTS

    sf::Font* DEFAULT_FONT;
};
