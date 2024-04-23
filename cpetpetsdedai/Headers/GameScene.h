#pragma once
#include "Scene.h"
#include "Camera.h"
#include "GraphicDebugger.h"
#include "PhysicsEngine.h"
#include "SceneManager.h"
#include "Animation.h"
#include "Animator.h"

class GameScene : public Scene
{
public:
	GameScene();

	void InitializeScene(sf::RenderWindow* _window) override;
	void Update(float deltaTime) override;

	void GameLoop(float deltaTime);

	void DestroyScene() override;
	void OnKeyDown(sf::Keyboard::Key pressedKey) override;
	void OnPlayerCollisionEnter(Collider* _collideWith, sf::Vector2f _collisionPoint);
	std::shared_ptr<Collider> playerCollider;
protected:
	virtual void InitLevel() = 0;
	virtual void SetupMapElements() = 0;
	virtual void SetupElements() = 0;

	void OnSceneChanged();


	std::shared_ptr<GameObject> mainCameraObject;
	Camera mainCamera;
	PhysicsEngine physicsEngine;
	GraphicDebugger graphicDebugger;
	std::shared_ptr<GameObject> Player;
	std::shared_ptr<GameObject> Ground;
	std::shared_ptr<BoxCollider> groundCollider;
	std::shared_ptr<GameObject> directionArrow;
	std::shared_ptr<GameObject> forceArrow;
	std::shared_ptr<GameObject> BackgroundObject;

	Animator playerAnimator;
	Animation IdleAnimation;
	std::vector<Animation> playerAnimations;
	
	std::shared_ptr<GameObject> CreateBackground();
	std::tuple<std::shared_ptr<GameObject>, std::shared_ptr<Collider>> CreatePlayer();
	std::tuple<std::shared_ptr<GameObject>, std::shared_ptr<CustomCollider>> CreateTarget();


	int currentLevel;


	sf::Font font;
	sf::Text ThrowsText;
	sf::Text LevelText;
};
