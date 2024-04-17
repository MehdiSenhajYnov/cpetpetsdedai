#pragma once
#include <map>
#include <string>
#include <SFML/Graphics/Texture.hpp>

class TextureManager
{
private:
    static TextureManager* instance;
    TextureManager() = default;
    std::map<std::string, sf::Texture*> textures;
public:
    void Init();
    static TextureManager* Instance();
    ~TextureManager();
    sf::Texture* GetTexture(std::string _texturePath);
    void DeleteTexture(std::string _texturePath);
    void DeleteAllTextures();
};
