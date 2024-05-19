#include "../../Headers/PhysicsComponents/CustomCollider.h"
#include "../../Headers/Engine/GameObject.h"


CustomCollider::CustomCollider() : Collider("CustomCollider", Collider::GetStaticType())
{
}

void CustomCollider::Init(TList<sf::Vector2f> allPoints)
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
