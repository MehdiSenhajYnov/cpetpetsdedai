#pragma once
#include "../../Headers/PhysicsComponents/BoxCollider.h"
#include "../../Headers/Engine/GameObject.h"

BoxCollider::BoxCollider()
{

}

void BoxCollider::Init(sf::Vector2f _topLeftPoint, sf::Vector2f _size)
{
	Collider::Init(
		{
			_topLeftPoint, _topLeftPoint + sf::Vector2f(_size.x,0),
			_topLeftPoint+_size, _topLeftPoint + sf::Vector2f(0,_size.y)
		});

}




void BoxCollider::Start()
{
}

void BoxCollider::ColliderUpdate(float deltaTime)
{
	if (shape_ptr != nullptr)
	{
		shape_ptr->setPosition(gameObject->GetPosition());
	}
}


