#pragma once
#include "../Engine/Object.h"

class GameObject;

class Component : public Object
{
public:
	Component();
	Component(const std::string& _typeName, Type* parentType);
	
	virtual ~Component() = default;
	AddType(Component, Object::GetStaticType())
	
	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;

	std::shared_ptr<GameObject> GetAttachedObject();

protected:
	virtual void Init(std::shared_ptr<GameObject> _gameObject);
	std::shared_ptr<GameObject> gameObject;
};

