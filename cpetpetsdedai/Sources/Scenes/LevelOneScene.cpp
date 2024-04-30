#include "../../Headers/Scenes/LevelOneScene.h"
#include "../../Headers/Engine/GameObject.h"
#include "../../Headers/PhysicsComponents/BoxCollider.h"
#include "../../Headers/PhysicsComponents/CustomCollider.h"


LevelOneScene::LevelOneScene()
{
}

void LevelOneScene::Update(float deltaTime)
{
	GameLoop(deltaTime);
}

void LevelOneScene::InitLevel()
{
	currentLevel = 1;

}

void LevelOneScene::SetupMapElements()
{
	BackgroundObject = CreateBackground();
}

void LevelOneScene::SetupElements()
{
	Ground = CreateGameObject("ground");
	BoxCollider* groundCollider = physicsEngine.CreateBoxCollider(Ground, sf::Vector2f(0,0), sf::Vector2f(800, 200));
	
	Ground->SetPosition(0, 900);
	groundCollider->Gravity = false;
	
	auto[Player, playerCollider] = CreatePlayer();
	Player->SetPosition(-20, 600);
	playerCollider->Gravity = true;

	auto[targetObj, targetCollider] = CreateTarget();
	targetCollider->Gravity = false;
	targetObj->SetPosition(6900, 790);

}

