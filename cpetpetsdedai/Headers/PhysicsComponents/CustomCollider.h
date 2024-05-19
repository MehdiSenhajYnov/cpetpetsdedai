#pragma once
#include <memory>
#include <vector>

#include "Collider.h"

class GameObject;

class CustomCollider : public Collider
{
public:
	ADD_TYPE(CustomCollider, Collider, REG_TYPE)
	CustomCollider();
	void Init(TList<sf::Vector2f> allPoints);
	void Start() override;
private:

	void ColliderUpdate(float deltaTime) override;

};

