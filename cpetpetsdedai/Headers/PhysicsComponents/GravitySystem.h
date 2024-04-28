#pragma once
#include <SFML/System/Vector2.hpp>
#include "../Components/Component.h"

class BoxCollider;
class PhysicsEngine;
class GameObject;

class GravitySystem : public Component
{
public:
	GravitySystem();
	void Init(BoxCollider* _boxCollider, PhysicsEngine* _physicsEngine);
	// Hérité via Component
	void Start() override;
	void Update(float deltaTime) override;

	void SetGravity(float _newGravityForce);
private:
	PhysicsEngine* physicsEngine;
	BoxCollider* boxCollider;
	float multiplier;
	float gravityForce;
	bool isGravityEnable;
	float minY;
	float maxY = 900;
	bool canBounce;
};

