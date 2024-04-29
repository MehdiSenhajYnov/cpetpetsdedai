#pragma once
#include <memory>
#include <SFML/System/Vector2.hpp>
#include "Collider.h"

class CircleCollider : public Collider
{
public:
	CircleCollider();
	void Init(sf::Vector2f _topLeftPoint, float radius, int accuracy);
private:
	void Start() override;
	void ColliderUpdate(float deltaTime) override;
};

