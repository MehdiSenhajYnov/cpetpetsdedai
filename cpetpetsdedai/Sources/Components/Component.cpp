#pragma once
#include "../../Headers/Components/Component.h"

#include "../../Headers/Engine/GameObject.h"

Component::Component() : Object("Component", Object::GetStaticType())
{
}

Component::Component(const std::string& _typeName, Type* parentType) : Object(_typeName, parentType)
{
}

void Component::Init(std::shared_ptr<GameObject> _gameObject)
{
	gameObject = _gameObject;
}

std::shared_ptr<GameObject> Component::GetAttachedObject()
{
	return gameObject;
}