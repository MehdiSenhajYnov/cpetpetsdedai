#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>
#include <future>
#include <memory>

class Collider;
class GraphicDebugger;
class Scene;
class GameObject;
class BoxCollider;
class CircleCollider;
class CustomCollider;


class PhysicsEngine
{
public:
	PhysicsEngine();
	void Init(Scene* _scene, GraphicDebugger* _graphicDebugger);

	bool ObjectCanMoveBy(Collider* colliderToCheck, sf::Vector2f _moveBy);
	//bool IsColliderTouchingCollider(Collider* firstCollider, Collider* Collider);
	bool SomeObjecsAreColliding();
	BoxCollider* CreateBoxCollider(GameObject* _gameObject, sf::Vector2f _topLeftPoint, sf::Vector2f _size);
	CircleCollider* CreateCircleCollider(GameObject* _gameObject, sf::Vector2f _topLeftPoint, float radius, int accuracy);
	CustomCollider* CreateCustomCollider(GameObject* _gameObject, std::vector<sf::Vector2f> allPoints);
	
	BoxCollider* CreateBoxCollider(GameObject* _gameObject, sf::Vector2f _topLeftPoint, sf::Vector2f _size, std::string _colliderID);
	CircleCollider* CreateCircleCollider(GameObject* _gameObject, sf::Vector2f _topLeftPoint, float radius, int accuracy, std::string _colliderID);
	CustomCollider* CreateCustomCollider(GameObject* _gameObject, std::vector<sf::Vector2f> allPoints, std::string _colliderID);

	
	void DestroyCollider(Collider* _colliderToRemove);
	void EnterModifyMode();
	void ExitModifyMode();
	void SwitchModifyMode();
	void SetModifyMode(bool newState);

	void UpdatePhysics(float deltaTime);

private:
	Scene* scene;
	std::vector<Collider*> AllColliders;
	sf::FloatRect TestRect;
	bool modifyMode;
	bool ShapeAreTouching(sf::Vector2f CenterShape1, sf::Vector2f OffsetShape1, std::vector<sf::Vector2f> Shape1AllPoints, sf::Vector2f CenterShape2, sf::Vector2f OffsetShape2, std::vector<sf::Vector2f> Shape2AllPoints);
	bool ShapeAreTouching(sf::Vector2f CenterShape1, sf::Vector2f OffsetShape1, std::vector<sf::Vector2f> Shape1AllPoints, sf::Vector2f CenterShape2, sf::Vector2f OffsetShape2, std::vector<sf::Vector2f> Shape2AllPoints, sf::Vector2f& OutCollisionPoint, sf::Vector2f& OutComplementaryAxePoint1, sf::Vector2f& OutComplementaryAxePoint2);
	bool TwoObjectAreColliding(Collider* c1, Collider* c2);
	sf::Vector2f CalculateNormalForceVector(Collider* c1, Collider* c2, sf::Vector2f ContactPoint, sf::Vector2f ComplementaryAxePoint1, sf::Vector2f ComplementaryAxePoint2);
	bool point_in_polygon(sf::Vector2f point, std::vector<sf::Vector2f> polygon, sf::Vector2f offest);

	GraphicDebugger* graphicDebugger;
	bool MoveObject(Collider* _colliderToMove, sf::Vector2f _moveby, float deltaTime);

};

