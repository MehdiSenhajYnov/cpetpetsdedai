#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "DrawableComponent.h"

class SpriteRenderer : public DrawableComponent
{
public:
    SpriteRenderer();
    AddType(SpriteRenderer, DrawableComponent::GetStaticType())
    ~SpriteRenderer() override;

    void Start() override;

    sf::Sprite* GetSprite();
    void SetSprite(const std::string& texturepath);

    void SetSprite(const std::string& _spriteName, sf::IntRect textureRect);
    void SetTexture(sf::Texture* _texture);
    void SetTexture(const sf::Texture* _texture);

    void SetColor(sf::Color _color);
    sf::Color GetColor();
    
    const sf::Drawable* GetDrawable() override;
    void setPosition(sf::Vector2f pos) override;

    sf::FloatRect GetBounds() override;
    
    sf::Vector2f GetSize() override;

    void SetOrigin(sf::Vector2f origin);
    void SetDrawScale(sf::Vector2f _drawScale) override;

private:

    sf::Texture* spriteTexture;
    sf::Sprite sprite;
    sf::Color color;
};
