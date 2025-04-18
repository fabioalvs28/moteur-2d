﻿#include "Texture.h"

#include "Engine/Utils/Debug.h"

Texture::Texture(std::string name, bool customPath) : mPath(name)
{
    if (!loadFromFile(customPath ? "" : "../../res/Textures/" + name))
    {
        Debug::Error("La texture ../../res/Textures/" + name + " was not found.");
    }
}
