#pragma once
#include "../../Headers/PhysicsComponents/CustomCollider.h"
#include "../../Headers/Engine/GameObject.h"



CustomCollider::CustomCollider()
{
}

void CustomCollider::Init(std::shared_ptr<GameObject> _gameObject, std::vector<sf::Vector2f> allPoints)
{
	Collider::Init(_gameObject, allPoints);
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
