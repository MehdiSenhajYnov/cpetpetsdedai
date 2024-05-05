#pragma once
#include "Headers/Engine/Object.h"
#include "Sources/EngineUIElement.h"


class Panel : public EngineUIElement
{
public:
    DefaultConstructor(Panel,EngineUIElement)
    AddType(Panel, EngineUIElement::GetStaticType())
    sf::Drawable* GetDrawable() override;
    void Update() override;

public:



private:
    
};
