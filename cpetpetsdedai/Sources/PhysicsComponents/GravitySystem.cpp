#pragma once
#include <iostream>
#include "../../Headers/PhysicsComponents/GravitySystem.h"
#include "../../Headers/Engine/GameObject.h"



GravitySystem::GravitySystem()
{

}

void GravitySystem::Init(BoxCollider* _boxCollider, PhysicsEngine* _physicsEngine)
{
	boxCollider = _boxCollider; 
	physicsEngine = _physicsEngine; 
	gravityForce = 9.0f; 
	isGravityEnable = true; 
	canBounce = true; 
	multiplier = 100;

	minY = gameObject->GetPosition().y;
}

void GravitySystem::Start()
{
}

void GravitySystem::Update(float deltaTime)
{
	if (gameObject->GetPosition().y > maxY)
	{
		multiplier = -100;
	}
	if (gameObject->GetPosition().y < minY)
	{
		multiplier = 100;
	}

	//gameObject->Move(0, gravityForce * multiplier * deltaTime);
	//physicsEngine->MoveObject(boxCollider, sf::Vector2f(0,gravityForce * multiplier * deltaTime));
}

void GravitySystem::SetGravity(float _newGravityForce)
{
	gravityForce = _newGravityForce;
}
