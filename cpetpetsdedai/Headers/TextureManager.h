#pragma once
#include <map>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <ostream>


class TextureManager
{
private:
    static TextureManager* instance;
    TextureManager() = default;
    std::map<std::string, sf::Texture*> textures;

    void IncludeIdleAnimationTextures();
    void AutoInclude(const std::string& mapNamePattern, const std::string& path, const std::string& pattern, int _counterAmount, const std::string& fileExtension,int amount);
public:
    static void ResetInstance();
    void Init();
    static TextureManager* Instance();
    ~TextureManager();
    void AddTexture(std::string mapName, std::string _texturePath);
    sf::Texture* GetTexture(std::string _textureName);
    void DeleteTexture(std::string _texturePath);
    void DeleteAllTextures();
};
