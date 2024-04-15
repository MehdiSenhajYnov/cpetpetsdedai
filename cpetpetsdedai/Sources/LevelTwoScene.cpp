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

	auto [ground1, ground1Collider] = CreatePlatformeThree();
	ground1->SetPosition(150, 650);

	std::get<0>(CreatePlatformeThree())->SetPosition(2000, 250);

	std::get<0>(CreatePlatformeTwo())->SetPosition(3300, 400);

	std::get<0>(CreatePlatformeOne())->SetPosition(5000, 250);

	std::get<0>(CreatePlatformeOne())->SetPosition(6800, 800);
}

void LevelTwoScene::SetupElements()
{
	tie(Player, playerCollider) = CreatePlayer();
	playerCollider->Gravity = true;


	auto [targetObj, targetCollider] = CreateTarget();
	targetCollider->Gravity = false;
	targetObj->SetPosition(6900, 790);

}

