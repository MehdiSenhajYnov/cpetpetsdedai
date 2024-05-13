#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "DrawableComponent.h"

class SpriteRenderer : public DrawableComponent
{
protected:
    SpriteRenderer(const std::string& _name, Type* parentType);
    SpriteRenderer(const uint64_t& _id, const std::string& _name, Type* parentType);
public:
    SpriteRenderer();
    SpriteRenderer(uint64_t _id);

    AddType(SpriteRenderer, DrawableComponent)
    ~SpriteRenderer() override;

    void Start() override;

    sf::Sprite* GetSprite();

    void SetSprite(const std::string& texturepath);
    void SetSprite(const std::string& _spriteName, sf::IntRect textureRect);
    void SetTexture(sf::Texture* _texture);
    void SetTexture(const sf::Texture* _texture);

    void      SetColor(const sf::Color& _color) override;
    sf::Color GetColor() const override;
    
    const sf::Drawable* GetDrawable() override;
    void setPosition(sf::Vector2f pos) override;

    sf::FloatRect GetBounds() override;
    
    sf::Vector2f GetOriginalSize() override;

    void SetOrigin(sf::Vector2f origin);
    void ResetOrigin();
    void SetDrawScale(sf::Vector2f _drawScale) override;

    sf::Vector2f GetCenter() const;

private:
    std::string spriteName;
    sf::Texture* spriteTexture;
    sf::Sprite sprite;
    sf::Color color;
};
