#include "../../Headers/GameSystem/TextureManager.h"

TextureManager* TextureManager::instance;

TextureManager::TextureManager() : GameSystem("TextureManager", GameSystem::GetStaticType())
{
}

TextureManager::~TextureManager()
{
    std::cout << "Deleting TextureManager" << std::endl;
    DeleteAllTextures();
}

TextureManager* TextureManager::Instance()
{
    if (instance == nullptr)
    {
        instance = new TextureManager();
    }
    return instance;
}

void TextureManager::AddTexture(std::string mapName, std::string _texturePath)
{
    if (!textures.contains(mapName) || textures[mapName] == nullptr)
    {
        textures[mapName] = new sf::Texture();
    }
    textures[mapName]->loadFromFile(_texturePath);
    textures[mapName]->setSmooth(true);
}

void TextureManager::Init()
{
    std::cout << "TextureManager initializing ..." << std::endl;

    AddTexture("TestObj", "./Assets/TestObj.png");
    AddTexture("Square", "./Assets/Square.png");
    AddTexture("RoundedRectangle", "./Assets/RoundedRectangle.png");
    AddTexture("EditorMove", "./Assets/Editor/MoveArrow.png");
    IncludeIdleAnimationTextures();
}

sf::Texture* TextureManager::GetTexture(std::string _textureName)
{
    if (textures.contains(_textureName))
    {
        return textures[_textureName];
    }
    std::cout << "Texture not found: " << _textureName << std::endl;
    return nullptr;
}

void TextureManager::DeleteTexture(std::string _texturePath)
{
    if (textures.contains(_texturePath))
    {
        auto test = textures[_texturePath];
        delete test;
        test = nullptr;
        textures.erase(_texturePath);

        
    }
}

void TextureManager::DeleteAllTextures()
{
    for (auto& [textureName, texture] :textures)
    {
        delete texture;
        texture = nullptr;
    }
    std::cout << "Textures cleared" << std::endl;
    textures.clear();
}

void TextureManager::IncludeIdleAnimationTextures()
{
    AutoInclude("PLAYERIDLE", "./Assets/PlayerAnimations/Idle/", "PLAYERIDLE", 3, ".png", 6);
}


void TextureManager::AutoInclude(const std::string& mapNamePattern, const std::string& path, const std::string& pattern, int _counterAmount, const std::string& fileExtension, int amount)
{
    std::string nbString;
    int nbOfZeroToAdd;
    for (int i = 1; i <= amount; i++)
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
        std::cout<< "adding texture: " << mapNamePattern + nbString << " from: " << fullPath << std::endl;
        AddTexture(mapNamePattern + nbString, fullPath);
    }
}

void TextureManager::ResetInstance()
{
    if(instance != nullptr)
    {
        delete instance;
        instance = nullptr;
    }
    
}
