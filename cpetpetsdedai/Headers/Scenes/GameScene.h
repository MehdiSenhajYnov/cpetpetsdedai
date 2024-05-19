#pragma once
#include "Scene.h"
#include "../Animation.h"

class Collider;
class BoxCollider;
class CustomCollider;

class GameScene : public Scene
{
public:
	GameScene();
	ADD_TYPE(GameScene, Scene, REG_TYPE)

	void InitializeScene(sf::RenderWindow* _window) override;
	void UpdatePreComponent(float deltaTime) override;
	void UpdatePostComponent(float deltaTime) override;
	
	void DestroyScene() override;
	void OnKeyDown(sf::Keyboard::Key pressedKey) override;
	void OnPlayerCollisionEnter(Collider* _collideWith, sf::Vector2f _collisionPoint);
	Collider* playerCollider;
protected:
	virtual void InitLevel() = 0;
	virtual void SetupMapElements() = 0;
	virtual void SetupElements() = 0;

	void OnSceneChanged();

	GameObject* Player;
	
	GameObject* Ground;
	GameObject* directionArrow;
	GameObject* forceArrow;
	GameObject* BackgroundObject;

	std::vector<Animation> playerAnimations;
	
	GameObject* CreateBackground();
	std::tuple<GameObject*, Collider*> CreatePlayer();
	std::tuple<GameObject*, CustomCollider*> CreateTarget();

	int currentLevel;


	sf::Font font;
	sf::Text ThrowsText;
	sf::Text LevelText;
};
