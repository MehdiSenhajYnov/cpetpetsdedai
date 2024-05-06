﻿#pragma once
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

    sf::Texture* spriteTexture;
    sf::Sprite sprite;
    sf::Color color;
};