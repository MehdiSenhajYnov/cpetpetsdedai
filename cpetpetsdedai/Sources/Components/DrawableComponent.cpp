#include "../../Headers/Components/DrawableComponent.h"

#include "../../Headers/Engine/GameObject.h"

DrawableComponent::DrawableComponent() : Component("DrawableComponent", Component::GetStaticType())
{
}

DrawableComponent::DrawableComponent(const std::string& _typeName, Type* parentType) : Component(_typeName, parentType)
{
}

DrawableComponent::~DrawableComponent()
{
}

void DrawableComponent::Init()
{
    gameObject->AddDrawableComponent(this);
}
