#include "BaseComponent.h"

BaseComponent::BaseComponent() : BaseComponent("BaseComponent", Object::GetStaticType())
{
}

BaseComponent::BaseComponent(const std::string& _typeName, Type* parentType) : Object(_typeName, parentType)
{
}

void BaseComponent::Init()
{
}

void BaseComponent::InitBaseComponent(GameObject* _gameObject)
{
    gameObject = _gameObject;
}

GameObject* BaseComponent::GetAttachedObject()
{
    return gameObject;
}
