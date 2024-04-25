#include "../../Headers/PhysicsComponents/CircleCollider.h"
#include "../../Headers/Utilities/MyMath.h"
#include "../../Headers/Engine/GameObject.h"


CircleCollider::CircleCollider()
{
}

void CircleCollider::Init(std::shared_ptr<GameObject> _gameObject, sf::Vector2f _topLeftPoint, float radius, int accuracy)
{
	std::vector<sf::Vector2f> _allpoints = MyMath::GetPointsOfPolygonInCircle(_topLeftPoint,radius, accuracy);
	Collider::Init(_gameObject, _allpoints);
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
