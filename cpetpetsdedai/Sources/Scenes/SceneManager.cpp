#include "../../Headers/Scenes/SceneManager.h"


void SceneManager::ChangeScene(SceneEnum newScene)
{
	currentSceneType = newScene;
	OnSceneChanged.InvokeEvent(newScene);
}

SceneManager* SceneManager::GetInstance()
{
    static SceneManager* instance;
    if (instance == nullptr)
    {
        instance = new SceneManager();
    }
    return instance;
}

void SceneManager::ResetInstance()
{
    auto instance = GetInstance();
    delete instance;
    instance = nullptr;
}

void SceneManager::SetLevel(int newLevel)
{
    if (newLevel == 0)
    {
        ChangeScene(SceneEnum::Menu);
    }
    else if (newLevel == 1) 
    {
        ChangeScene(SceneEnum::Level1);
    }
    else
    {
        ChangeScene(SceneEnum::Menu);
    }

	//currentSceneType = newScene;
	//OnSceneChanged.InvokeEvent(newScene);
}

Scene* SceneManager::GetCurrentScene() const
{
    return currentScene;
}

void SceneManager::SetCurrentScene(Scene* newScene)
{
    currentScene = newScene;
}
