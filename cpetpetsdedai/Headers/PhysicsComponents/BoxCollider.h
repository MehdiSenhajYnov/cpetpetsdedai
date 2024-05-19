#pragma once
#include <SFML/System/Vector2.hpp>
#include "Collider.h"



class BoxCollider : public Collider
{
public:
	ADD_TYPE(BoxCollider, Collider, REG_TYPE)
	BoxCollider();
	void Init(sf::Vector2f _topLeftPoint, sf::Vector2f _size);
	void Start() override;
private:

	void ColliderUpdate(float deltaTime) override;
};

