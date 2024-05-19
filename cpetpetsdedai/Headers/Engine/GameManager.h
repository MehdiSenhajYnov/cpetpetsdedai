#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Object.h"
#include "../Scenes/SceneManager.h"

class GameManager : public Object
{
public:
	GameManager();
	~GameManager() override;
	void Run();
	void OnChangeSceneAsked(SceneManager::SceneEnum sceneToUse);
	void ChangeScene(SceneManager::SceneEnum sceneToUse);
	void DeleteScene();
	
private:
	SceneManager::SceneEnum newScene = SceneManager::SceneEnum::Menu;
	bool haveToChangeScene = false;
	bool iswindowFocus;
	void WindowsEvents();
	void InputEvents();

	sf::RenderWindow window;

	TList<sf::Event> eventsOfTick;
};

