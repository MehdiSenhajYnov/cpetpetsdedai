#include "../Headers/LevelThreeScene.h"

LevelThreeScene::LevelThreeScene()
{
}


void LevelThreeScene::Update(float deltaTime)
{
	mainCamera.Render();
	GameLoop(deltaTime);
}

void LevelThreeScene::InitLevel()
{
	currentLevel = 3;
}

void LevelThreeScene::SetupMapElements()
{
	BackgroundObject = CreateBackground();

}

void LevelThreeScene::SetupElements()
{
	tie(Player, playerCollider) = CreatePlayer();
	playerCollider->Gravity = true;


	auto [targetObj, targetCollider] = CreateTarget();
	targetCollider->Gravity = false;
	targetObj->SetPosition(6900, 790);

}

