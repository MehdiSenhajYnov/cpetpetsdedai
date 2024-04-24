#pragma once
#include "GameObject.h"

class Component : public Object
{
public:
	Component();
	virtual void Start() = 0;
	virtual void Update(float deltaTime) = 0;

	void LoadComponentBase(std::shared_ptr<GameObject> _gameObject);
	std::shared_ptr<GameObject> GetAttachedObject();

protected:
	std::shared_ptr<GameObject> gameObject;
};

