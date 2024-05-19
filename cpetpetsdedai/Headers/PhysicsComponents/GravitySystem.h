#pragma once
#include <SFML/System/Vector2.hpp>
#include "../Components/Component.h"

class BoxCollider;
class PhysicsEngine;
class GameObject;

class GravitySystem : public Component
{
public:
	ADD_TYPE(GravitySystem, Component, REG_TYPE)
	GravitySystem();
	void Init(BoxCollider* _boxCollider, PhysicsEngine* _physicsEngine);
	// Hérité via Component
	void Start() override;
	void Update(float deltaTime) override;

	void SetGravity(float _newGravityForce);
private:
	PhysicsEngine* physicsEngine = nullptr;
	BoxCollider* boxCollider = nullptr;
	float multiplier = 0;
	float gravityForce = 0;
	bool isGravityEnable = false;
	float minY = 0;
	float maxY = 900;
	bool canBounce = false;
};

