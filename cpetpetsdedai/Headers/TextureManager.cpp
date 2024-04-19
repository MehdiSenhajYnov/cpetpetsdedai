#include "TextureManager.h"

TextureManager* TextureManager::instance;

TextureManager::~TextureManager()
{
    DeleteAllTextures();
}


void TextureManager::Init()
{

    
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

void TextureManager::IncludeIdleAnimationTextures()
{
    textures["PLAYERIDLE001"] = new sf::Texture();
    textures["PLAYERIDLE001"]->loadFromFile("./Assets/PlayerAnimations/Idle/PLAYERIDLE001.png");
}

void TextureManager::AutoInclude(std::string mapName, std::string path, std::string pattern, int _counterAmount, std::string fileExtension,int amount)
{
    textures[mapName] = new sf::Texture();
    std::string nbString = "";
    int nbOfZeroToAdd;
    for (int i = 0; i < amount; i++)
    {
        nbString = std::to_string(i);
        if (nbString.length() < _counterAmount)
        {
            nbOfZeroToAdd = _counterAmount - nbString.length();
            for (int j = 0; j < nbOfZeroToAdd; j++)
            {
                nbString = "0" + nbString;
            }
        }
        std::string fullPath = path + pattern + nbString + fileExtension;
        textures[mapName]->loadFromFile(fullPath);
    }
}
