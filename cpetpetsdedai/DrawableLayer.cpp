#include "DrawableLayer.h"

#include "Headers/Components/DrawableComponent.h"

DrawableLayer::DrawableLayer() : DrawableLayer("DrawableLayer", Object::GetStaticType()) { }
DrawableLayer::DrawableLayer(const std::string& _typeName, Type* parentType) : Object(_typeName, parentType) { }

DrawableLayer::DrawableLayer(int _zIndex): Object("DrawableLayer", Object::GetStaticType()), ZIndex(_zIndex)
{
    SERIALIZE_FIELD(ZIndex)
    SERIALIZE_FIELD(drawableComponents)
}

DrawableComponent* DrawableLayer::operator[](const int& index)
{
    return drawableComponents[index];
}

const DrawableComponent* DrawableLayer::operator[](const int& index) const
{
    return drawableComponents[index];
}
