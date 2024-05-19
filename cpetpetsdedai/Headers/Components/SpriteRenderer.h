#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "DrawableComponent.h"

class SpriteRenderer : public DrawableComponent
{
protected:
    SpriteRenderer(const std::string& _name, Type* parentType);
public:
    SpriteRenderer();

    ADD_TYPE(SpriteRenderer, DrawableComponent, REG_TYPE)
    ~SpriteRenderer() override;

    void Start() override;

    sf::Sprite* GetSprite();

    void SetSprite(std::string _spriteName);
    void SetSprite(const std::string& _spriteName, sf::IntRect textureRect);
    void SetTexture(sf::Texture* _texture);
    void SetTexture(const sf::Texture* _texture);

    void SetColorCSET(sf::Color _color);
    void      SetColor(const sf::Color& _color) override;
    sf::Color GetColor() const override;
    
    const sf::Drawable* GetDrawable() override;
    void setPosition(sf::Vector2f _pos) override;

    sf::FloatRect GetBounds() override;
    
    sf::Vector2f GetOriginalSize() override;

    void ResetOrigin();
    void SetDrawScale(sf::Vector2f _drawScale) override;

    sf::Vector2f GetCenter() const;
    void InternalSetOrigin(const sf::Vector2f _origin) override;
    void SetScale(sf::Vector2f _scale) override;

private:
    std::string spriteName;
    sf::Texture* spriteTexture;
    sf::Sprite sprite;
    sf::Color color;
};
