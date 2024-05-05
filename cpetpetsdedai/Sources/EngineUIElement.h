#pragma once
#include <SFML/Graphics/Drawable.hpp>

#include "../Headers/Engine/Object.h"

enum AnchorSide
{
    Left,
    Right,
    Top,
    Bottom
};


class EngineUIElement : public Object
{
public:
    DefaultConstructor(EngineUIElement, Object)
    AddType(EngineUIElement, Object::GetStaticType())

    virtual sf::Drawable* GetDrawable() = 0;
    virtual void Init() {}
    virtual void Update() = 0;
    virtual void PreDestroy() {}
    virtual ~EngineUIElement() override = default;


    std::string GetName() const { return name; }
    void SetName(const std::string& _name) { name = _name; }
    
    AnchorSide GetAnchorSide() const { return anchorSide; }
    void SetAnchorSide(AnchorSide _anchorSide) { anchorSide = _anchorSide; }

    float GetSize() const { return size; }
    void SetSize(float _size) { size = _size; }
    
protected:
    std::string name;
    AnchorSide anchorSide = AnchorSide::Left;
    float size = 300.0f;

};
