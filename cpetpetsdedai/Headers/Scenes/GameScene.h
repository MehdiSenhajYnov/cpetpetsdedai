#pragma once
#include "Scene.h"
#include "../Animation.h"
#include "../GameSystem/PhysicsEngine.h"
#include "../Utilities/GraphicDebugger.h"

class Collider;
class BoxCollider;
class CustomCollider;

class GameScene : public Scene
{
public:
	GameScene();
	AddType(GameScene, Scene::GetStaticType())

	void InitializeScene(sf::RenderWindow* _window) override;
	void Update(float deltaTime) override;

	void GameLoop(float deltaTime);

	void DestroyScene() override;
	void OnKeyDown(sf::Keyboard::Key pressedKey) override;
	void OnPlayerCollisionEnter(Collider* _collideWith, sf::Vector2f _collisionPoint);
	Collider* playerCollider;
protected:
	virtual void InitLevel() = 0;
	virtual void SetupMapElements() = 0;
	virtual void SetupElements() = 0;

	void OnSceneChanged();

	PhysicsEngine physicsEngine;
	GraphicDebugger graphicDebugger;
	
	std::shared_ptr<GameObject> Player;
	
	std::shared_ptr<GameObject> Ground;
	std::shared_ptr<GameObject> directionArrow;
	std::shared_ptr<GameObject> forceArrow;
	std::shared_ptr<GameObject> BackgroundObject;

	Animation IdleAnimation;
	std::vector<Animation> playerAnimations;
	
	std::shared_ptr<GameObject> CreateBackground();
	std::tuple<std::shared_ptr<GameObject>, Collider*> CreatePlayer();
	std::tuple<std::shared_ptr<GameObject>, CustomCollider*> CreateTarget();

	int currentLevel;


	sf::Font font;
	sf::Text ThrowsText;
	sf::Text LevelText;
};
