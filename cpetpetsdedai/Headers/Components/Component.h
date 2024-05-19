#pragma once
#include "../Engine/Object.h"

class GameObject;

enum ComponentWorkType
{
	PlayOnly,
	EditorOnly,
	PlayAndEditor,
};

struct ComponentInitParams {
	
};

class Component : public Object
{
protected:
	Component(const std::string& _name, Type* parentType);
public:
	Component();
	
	virtual ~Component() override = default;
	ADD_TYPE(Component, Object, REG_TYPE)
	
	virtual void Start() = 0;

	
	virtual void Update(float deltaTime) = 0;

	virtual void LateUpdate(float deltaTime) {};

	virtual void PreDestroy() override {}

	GameObject* GetAttachedObject();
	ComponentWorkType componentWorkType = PlayAndEditor;

	virtual void Init();

	virtual void InitBaseComponent(GameObject* _gameObject);
protected:

	GameObject* gameObject = nullptr;
	int gameObjectId = 0;

private:
};

