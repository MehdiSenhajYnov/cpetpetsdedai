#pragma once
#include "GameScene.h"


class LevelOneScene : public GameScene
{
public:
	LevelOneScene();
	void Update(float deltaTime) override;
private:
	void InitLevel() override;
	void SetupMapElements() override;
	void SetupElements() override;
};



