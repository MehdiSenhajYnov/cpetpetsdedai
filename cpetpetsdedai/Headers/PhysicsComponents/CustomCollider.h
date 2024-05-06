#pragma once
#include <memory>
#include <vector>

#include "Collider.h"

class GameObject;

class CustomCollider : public Collider
{
public:
	CustomCollider();
	void Init(std::vector<sf::Vector2f> allPoints);
private:

	void Start() override;
	void ColliderUpdate(float deltaTime) override;

};
