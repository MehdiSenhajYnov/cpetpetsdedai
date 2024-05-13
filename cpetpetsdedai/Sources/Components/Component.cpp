#include "../../Headers/Components/Component.h"
#include "../../Headers/Engine/GameObject.h"

Component::Component() : Component("Component", Object::GetStaticType())
{
}


Component::Component(const std::string& _typeName, Type* parentType) : Object(_typeName, parentType),
                                                                       componentWorkType(Play), gameObject(nullptr)
{
	SerializeField(ComponentWorkType, componentWorkType)
	SerializeField(GameObject*, gameObject)
}

Component::Component(const uint64_t& _id, const std::string& _name, Type* parentType): Object(_id, _name, parentType),
	componentWorkType(Play),
	gameObject(nullptr), gameObjectId(0)
{
	SerializeField(ComponentWorkType, componentWorkType)
	SerializeField(GameObject*, gameObject)
}

Component::Component(uint64_t _id): Component(_id, "Component", Object::GetStaticType()) {}


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
