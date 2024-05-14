#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Object.h"
#include "../Scenes/SceneManager.h"


class Scene;

class GameManager : public Object
{
public:
	GameManager();
	~GameManager();
	void Run();
	void OnChangeSceneAsked(SceneManager::SceneEnum sceneToUse);
	void ChangeScene(SceneManager::SceneEnum sceneToUse);
	void DeleteScene();
	
private:
	SceneManager::SceneEnum newScene;
	bool haveToChangeScene;
	bool iswindowFocus;
	void WindowsEvents();
	void InputEvents();

	Scene* currentScene;
	sf::RenderWindow window;

	TList<sf::Event> eventsOfTick;
};

