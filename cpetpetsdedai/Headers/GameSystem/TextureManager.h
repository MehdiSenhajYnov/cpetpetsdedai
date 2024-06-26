﻿#pragma once
#include <map>
#include <string>
#include <SFML/Graphics/Texture.hpp>
#include <ostream>
#include "GameSystem.h"

// SINGLETON
class TextureManager : public GameSystem
{

public:
    void Init();
    ADD_TYPE(TextureManager, GameSystem, REG_TYPE)
    void AutoInclude(const std::string& mapNamePattern, const std::string& path, const std::string& pattern, int _counterAmount, const std::string& fileExtension,int amount);
    sf::Texture* GetTexture(std::string _textureName);
    void AddTexture(std::string mapName, std::string _texturePath);
    void DeleteTexture(std::string _texturePath);
    void DeleteAllTextures();

    static void ResetInstance();
    ~TextureManager() override;
    static TextureManager* Instance();
private:
    std::map<std::string, sf::Texture*> textures;

    void IncludeIdleAnimationTextures();
    TextureManager();
    static TextureManager* instance;
};
