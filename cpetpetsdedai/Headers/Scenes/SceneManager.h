#pragma once
#include "../Utilities/Event.h"


class Scene;

class SceneManager
{
public:
	static SceneManager* GetInstance();
	static void ResetInstance();
	
	enum SceneEnum { Menu, Level1};
	SceneEnum currentSceneType;

	void SetLevel(int newLevel);
	Event<SceneEnum> OnSceneChanged;

	Scene* GetCurrentScene() const;
	void SetCurrentScene(Scene* newScene);
private:
	Scene* currentScene = nullptr;
	void ChangeScene(SceneEnum newScene);

};

