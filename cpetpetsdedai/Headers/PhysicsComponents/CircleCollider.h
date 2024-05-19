#pragma once
#include <memory>
#include <SFML/System/Vector2.hpp>
#include "Collider.h"

class CircleCollider : public Collider
{
public:
	ADD_TYPE(CircleCollider, Collider, REG_TYPE)
	CircleCollider();
	void Init(sf::Vector2f _topLeftPoint, float radius, int accuracy);
	void Start() override;
private:
	void ColliderUpdate(float deltaTime) override;
};

