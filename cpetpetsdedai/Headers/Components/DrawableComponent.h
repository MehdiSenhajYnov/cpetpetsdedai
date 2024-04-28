#pragma once
#include <SFML/Graphics/Drawable.hpp>
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
    void Init();

};
