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
	
	virtual ~Component() = default;
	AddType(Component, Object::GetStaticType())
	
	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;

	GameObject* GetAttachedObject();
	ComponentWorkType componentWorkType;

	virtual void Init(ComponentInitParams* Params);;
	void         InitBaseComponent(GameObject* _gameObject);
protected:

	GameObject* gameObject;
};

