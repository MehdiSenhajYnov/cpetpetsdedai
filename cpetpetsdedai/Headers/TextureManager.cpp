#include "TextureManager.h"

TextureManager* TextureManager::instance;

TextureManager::~TextureManager()
{
    DeleteAllTextures();
}
void TextureManager::Init()
{
    textures["PlayerIdle001"] = new sf::Texture();
}

sf::Texture* TextureManager::GetTexture(std::string _texturePath)
{
    if (textures.contains(_texturePath))
    {
        return textures[_texturePath];
    }
    return nullptr;
}

void TextureManager::DeleteTexture(std::string _texturePath)
{
    if (textures.contains(_texturePath))
    {
        delete textures[_texturePath];
        textures.erase(_texturePath);
    }
}

void TextureManager::DeleteAllTextures()
{
    for (auto& [textureName, texture] :textures)
    {
        delete texture;
    }
    textures.clear();
}



TextureManager* TextureManager::Instance()
{
    if (instance == nullptr)
    {
        instance = new TextureManager();
    }
    return instance;
}
