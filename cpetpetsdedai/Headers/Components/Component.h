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
protected:
	Component(const std::string& _name, Type* parentType);
	Component(const uint64_t& _id, const std::string& _name, Type* parentType);
public:
	Component();
	Component(uint64_t _id);


	
	virtual ~Component() override = default;
	AddType(Component, Object)
	
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

private:
};

