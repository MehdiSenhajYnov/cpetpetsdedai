#pragma once
#include "GameScene.h"
class LevelTwoScene : public GameScene
{
public:
	LevelTwoScene();
	void Update(float deltaTime) override;
private:
	void InitLevel() override;
	void SetupMapElements() override;
	void SetupElements() override;
};