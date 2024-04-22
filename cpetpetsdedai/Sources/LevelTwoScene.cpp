#include "../Headers/LevelTwoScene.h"

LevelTwoScene::LevelTwoScene()
{
}


void LevelTwoScene::Update(float deltaTime)
{
	mainCamera.Render();
	GameLoop(deltaTime);
}

void LevelTwoScene::InitLevel()
{
	currentLevel = 2;
}

void LevelTwoScene::SetupMapElements()
{
	BackgroundObject = CreateBackground();

}

void LevelTwoScene::SetupElements()
{
	tie(Player, playerCollider) = CreatePlayer();
	playerCollider->Gravity = true;


	auto [targetObj, targetCollider] = CreateTarget();
	targetCollider->Gravity = false;
	targetObj->SetPosition(6900, 790);

	
	
}

