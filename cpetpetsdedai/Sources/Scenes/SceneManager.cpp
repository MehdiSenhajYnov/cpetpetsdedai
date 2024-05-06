#include "../../Headers/Utilities/Event.h"
#include "../../Headers/Scenes/SceneManager.h"


SceneManager::SceneEnum SceneManager::currentScene;
Event<SceneManager::SceneEnum> SceneManager::OnSceneChanged;

void SceneManager::ChangeScene(SceneEnum newScene)
{
	currentScene = newScene;
	OnSceneChanged.InvokeEvent(newScene);
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

	//currentScene = newScene;
	//OnSceneChanged.InvokeEvent(newScene);
}