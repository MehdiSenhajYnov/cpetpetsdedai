#pragma once
#include <SFML/System/Vector2.hpp>
#include "Collider.h"



class BoxCollider : public Collider
{
public:
	BoxCollider();
	void Init(sf::Vector2f _topLeftPoint, sf::Vector2f _size);
private:

	void Start() override;
	void ColliderUpdate(float deltaTime) override;
};

