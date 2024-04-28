#pragma once
#include "../../Headers/PhysicsComponents/CustomCollider.h"
#include "../../Headers/Engine/GameObject.h"



CustomCollider::CustomCollider()
{
}

void CustomCollider::Init(std::vector<sf::Vector2f> allPoints)
{
	Collider::Init(allPoints);
}

void CustomCollider::Start()
{
}

void CustomCollider::ColliderUpdate(float deltaTime)
{
	if (shape_ptr != nullptr)
	{
		shape_ptr->setPosition(gameObject->GetPosition());
	}
}
