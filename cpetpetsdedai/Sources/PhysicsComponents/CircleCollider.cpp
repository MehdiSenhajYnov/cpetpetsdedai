#include "../../Headers/PhysicsComponents/CircleCollider.h"
#include "../../Headers/Utilities/MyMath.h"
#include "../../Headers/Engine/GameObject.h"


CircleCollider::CircleCollider() : Collider("CircleCollider", Collider::GetStaticType())
{
}

void CircleCollider::Init(sf::Vector2f _topLeftPoint, float radius, int accuracy)
{
	TList<sf::Vector2f> _allpoints = MyMath::GetPointsOfPolygonInCircle(_topLeftPoint,radius, accuracy);
	Collider::Init(_allpoints);
}

void CircleCollider::Start()
{
}

void CircleCollider::ColliderUpdate(float deltaTime)
{
	if (shape_ptr != nullptr)
	{
		shape_ptr->setPosition(gameObject->GetPosition());
	}

}
