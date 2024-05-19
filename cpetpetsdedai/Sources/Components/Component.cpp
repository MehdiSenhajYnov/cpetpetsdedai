#include "../../Headers/Components/Component.h"
#include "../../Headers/Engine/GameObject.h"

Component::Component() : Component("Component", Object::GetStaticType())
{
}


Component::Component(const std::string& _typeName, Type* parentType) : Object(_typeName, parentType)
{
	SERIALIZE_FIELD(componentWorkType)
	SERIALIZE_FIELD(gameObject)
}

void Component::Init()
{
}

void Component::InitBaseComponent(GameObject* _gameObject)
{
	gameObject = _gameObject;
	gameObjectId = _gameObject->GetId();
}

GameObject* Component::GetAttachedObject()
{
	return gameObject;
}
