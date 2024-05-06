#pragma once
#include "../Engine/Object.h"

class GameObject;

enum ComponentWorkType
{
	Play,
	Editor,
	PlayAndEditor,
};

struct ComponentInitParams {
	
};

class Component : public Object
{
public:
	Component();
	Component(const std::string& _typeName, Type* parentType);
	
	virtual ~Component() override = default;
	AddType(Component, Object::GetStaticType())
	
	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;
	virtual void PreDestroy() override {}

	GameObject* GetAttachedObject();
	ComponentWorkType componentWorkType;

	virtual void Init();

	virtual void InitBaseComponent(GameObject* _gameObject);
protected:

	GameObject* gameObject;
	int gameObjectId;
};

