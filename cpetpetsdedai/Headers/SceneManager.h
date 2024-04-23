#pragma once
#include "Event.h"

class SceneManager
{
public:
	enum SceneEnum { Menu, Level1};
	static SceneEnum currentScene;

	static void SetLevel(int newLevel);
	static Event<SceneManager::SceneEnum> OnSceneChanged;
private:
	static void ChangeScene(SceneEnum newScene);

};

