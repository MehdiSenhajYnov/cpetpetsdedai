#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Color.hpp>
#include "Component.h"


class DrawableComponent : public Component
{
public:
    DrawableComponent();
    DrawableComponent(const std::string& _typeName, Type* parentType);
    AddType(DrawableComponent, Component::GetStaticType())
    ~DrawableComponent() override;

    virtual const sf::Drawable* GetDrawable() = 0;
    virtual void setPosition(sf::Vector2f pos) = 0;

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
    void SetScale(sf::Vector2f _scale);

    sf::Vector2f GetOffsetPosition() const;
    void SetOffsetPosition(sf::Vector2f _offsetPosition);

    virtual sf::Color GetColor() const = 0;
    virtual void SetColor(const sf::Color& _color) = 0;
    
    
private:
    bool alreadyInit = false;
    sf::Vector2f Scale;
    sf::Vector2f OffsetPosition;


};
