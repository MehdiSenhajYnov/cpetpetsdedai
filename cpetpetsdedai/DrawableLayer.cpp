#include "DrawableLayer.h"

#include "Headers/Components/DrawableComponent.h"

DrawableLayer::DrawableLayer() : DrawableLayer("DrawableLayer", Object::GetStaticType()) { }
DrawableLayer::DrawableLayer(const std::string& _typeName, Type* parentType) : Object(_typeName, parentType) { }
DrawableLayer::DrawableLayer(uint64_t _id): DrawableLayer(_id, "DrawableLayer", Object::GetStaticType()) {}
DrawableLayer::DrawableLayer(const uint64_t& _id, const std::string& _name, Type* parentType): Object(_id, _name, parentType) {}

DrawableLayer::DrawableLayer(int _zIndex): Object("DrawableLayer", Object::GetStaticType()), ZIndex(_zIndex)
{
    
}

DrawableComponent* DrawableLayer::operator[](const int& index)
{
    return drawableComponents[index];
}

const DrawableComponent* DrawableLayer::operator[](const int& index) const
{
    return drawableComponents[index];
}
