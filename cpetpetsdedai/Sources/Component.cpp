#pragma once
#include "../Headers/Component.h"

Component::Component() : Object("Component", Object::ObjectType())
{
}

void Component::LoadComponentBase(std::shared_ptr<GameObject> _gameObject)
{
	gameObject = _gameObject;
}

std::shared_ptr<GameObject> Component::GetAttachedObject()
{
	return gameObject;
}