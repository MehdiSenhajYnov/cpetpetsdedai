#include "../Headers/LevelOneScene.h"

LevelOneScene::LevelOneScene()
{
}

void LevelOneScene::Update(float deltaTime)
{
	mainCamera.Render();
	GameLoop(deltaTime);
}

void LevelOneScene::InitLevel()
{
	currentLevel = 1;
	Ground = CreateGameObject("ground",-1);
	groundCollider = physicsEngine.CreateBoxCollider(Ground, sf::Vector2f(0,0), sf::Vector2f(10000, 200));
	Ground->SetPosition(0, 100);
}

void LevelOneScene::SetupMapElements()
{
	BackgroundObject = CreateBackground();
}

void LevelOneScene::SetupElements()
{
	tie(Player, playerCollider) = CreatePlayer();
	playerCollider->Gravity = true;

	auto[targetObj, targetCollider] = CreateTarget();
	targetCollider->Gravity = false;
	targetObj->SetPosition(6900, 790);

}

