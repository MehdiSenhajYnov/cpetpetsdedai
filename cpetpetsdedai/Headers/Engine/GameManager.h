#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

#include "../../TList.h"
#include "../Scenes/SceneManager.h"


class Scene;
template <typename T>
concept IsSceneClass = requires (T t) {
	t.InitializeScene();
	t.Update();
	t.OnKeyDown();
	t.DestroyScene();
};

class GameManager
{
public:
	GameManager();
	~GameManager();
	void Run();
	void OnChangeSceneAsked(SceneManager::SceneEnum sceneToUse);
	void ChangeScene(SceneManager::SceneEnum sceneToUse);

	
	template<typename T>
	void afficher_args(const T& arg) {
		std::cout << arg << std::endl;
	}
	
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

