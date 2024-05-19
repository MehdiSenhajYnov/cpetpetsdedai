#pragma once
#include "Headers/Engine/Object.h"

class DrawableComponent;

class DrawableLayer : public Object
{
public:
    ADD_TYPE(DrawableLayer, Object, REG_TYPE)
    DrawableLayer();
    DrawableLayer(const std::string& _name, Type* parentType);
    DrawableLayer(int _zIndex);

    int ZIndex = 0;
    TList<DrawableComponent*> drawableComponents;
    DrawableComponent* operator[](const int& index);
    const DrawableComponent* operator[](const int& index) const;
};
