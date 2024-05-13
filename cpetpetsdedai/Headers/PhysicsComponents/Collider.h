#pragma once
#include <map>
#include <memory>
#include <vector>
#include <SFML/Graphics/ConvexShape.hpp>
#include <SFML/System/Vector2.hpp>
#include "../Components/Component.h"
#include "../Utilities/Event.h"

class Camera;
class GameObject;

class Collider : public Component
{
public:
	Collider();

	virtual ~Collider();
	void SetVisible(bool _visibleState, Camera* cameraToUse);

	std::vector<sf::Vector2f> GetAllPoints();
	std::vector<sf::Vector2f> GetAllPointsOnObject();
	sf::Vector2f GetCenter();

	std::map< Collider*, sf::Vector2f> GetCurrentCollisions();

	void AddInCollisionWith(Collider* ColliderToAdd, sf::Vector2f ContactPoint);
	void RemoveFromCollisionWith(Collider* ColliderToRemove);
	bool AlreadyColliding(Collider* ColliderToCheck);

	void AddForce(sf::Vector2f forceToAdd);

	void SetVelocity(sf::Vector2f newVelocity);

	sf::Vector2f GetVelocity();
	bool Gravity;

	Event<Collider*, sf::Vector2f>* OnCollisionEnter();
	Event<Collider*>* OnCollisionExit();


	bool GetIsStatic();
	void SetIsStatic(bool _isStatic);
protected:
	virtual void Init(TList<sf::Vector2f> _allPoints);
	void CreateShape();
	TList<sf::Vector2f> allPoints;
	sf::Vector2f Center;

	std::map < Collider*, sf::Vector2f>  currentCollisions;

	sf::ConvexShape* shape_ptr;
	sf::ConvexShape shape;

	bool Visible;
	sf::Vector2f velocity;
	//sf::Vector2f acceleration;

	void FireCollisionEnter(Collider* CollideWith, sf::Vector2f ContactPoint);
	void FireCollisionExit(Collider* CollideWith);

	// Hérité via Component
	virtual void Start() = 0;
	void Update(float deltaTime);
	virtual void ColliderUpdate(float deltaTime) = 0;
	const float frictionForce = 0.99f;
	const float gravityForce = 90;

	bool IsStatic;

	Event<Collider*, sf::Vector2f> onCollisionEnter;
	Event<Collider*> onCollisionExit;
};
