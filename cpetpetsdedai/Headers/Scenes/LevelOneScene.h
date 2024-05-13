#pragma once
#include "GameScene.h"


class LevelOneScene : public GameScene
{
public:
	LevelOneScene();
private:
	void InitLevel() override;
	void SetupMapElements() override;
	void SetupElements() override;
};



