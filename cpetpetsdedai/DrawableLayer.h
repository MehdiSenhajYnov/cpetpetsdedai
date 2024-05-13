#pragma once
#include "Headers/Engine/Object.h"

class DrawableComponent;

class DrawableLayer : public Object
{
public:
    AddType(DrawableComponent, Object)
    DrawableLayer();
    DrawableLayer(const std::string& _name, Type* parentType);
    DrawableLayer(uint64_t _id);
    DrawableLayer(const uint64_t& _id, const std::string& _name, Type* parentType);
    DrawableLayer(int _zIndex);

    int ZIndex;	
    TList<DrawableComponent*> drawableComponents;
    DrawableComponent* operator[](const int& index);
    const DrawableComponent* operator[](const int& index) const;
};
