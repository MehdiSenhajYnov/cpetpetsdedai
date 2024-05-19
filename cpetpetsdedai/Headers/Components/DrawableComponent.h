#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include "Component.h"


class DrawableComponent : public Component
{
public:
    HeaderDefaultConstructor(DrawableComponent)
    ADD_TYPE(DrawableComponent, Component, REG_TYPE)

    ~DrawableComponent() override;

    virtual const sf::Drawable* GetDrawable() = 0;
    virtual void setPosition(sf::Vector2f _pos) = 0;

    virtual sf::Vector2f GetOriginalSize() = 0;
    virtual sf::Vector2f GetCurrentSize();
    
    virtual int GetZIndex()
    {
        return ZIndex;
    }
    virtual void SetZIndex(int _zIndex)
    {
        ZIndex = _zIndex;
    }

    int ZIndex = 0;
    
    virtual sf::FloatRect GetBounds() = 0;

    virtual void InitBaseComponent(GameObject* _gameObject) override;
    virtual void Init() override;
    void PreDestroy() override;
    virtual void Start() override = 0;
    virtual void Update(float deltaTime) override;

    virtual void SetDrawScale(sf::Vector2f _drawScale) = 0;

    sf::Vector2f GetScale() const;
    virtual void SetScale(sf::Vector2f _scale);

    sf::Vector2f GetOrigin() const;
    virtual void SetOrigin(const sf::Vector2f _origin);
    virtual void InternalSetOrigin(const sf::Vector2f _origin) = 0;

    sf::Vector2f GetOffsetPosition() const;
    void SetOffsetPosition(sf::Vector2f _offsetPosition);

    virtual sf::Color GetColor() const = 0;
    virtual void SetColor(const sf::Color& _color) = 0;
    
private:
    bool alreadyInit = false;
    sf::Vector2f Scale = {1, 1};
    sf::Vector2f OffsetPosition = {0, 0};
    sf::Vector2f Origin = {0, 0};

};
