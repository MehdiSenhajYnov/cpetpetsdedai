#pragma once

#include <SFML/Graphics/Vertex.hpp>

#include "Headers/Engine/Object.h"
#include "Sources/EngineUIElement.h"


class Panel : public EngineUIElement
{
public:
    DefaultConstructor(Panel,EngineUIElement)
    AddType(Panel, EngineUIElement::GetStaticType())
    sf::Drawable* GetDrawable() override;

    void          Init(sf::RenderWindow* window) override;
    void          Update() override;
    void          Draw(sf::RenderWindow* window) override;

private:
    sf::Vertex line[2];

};
