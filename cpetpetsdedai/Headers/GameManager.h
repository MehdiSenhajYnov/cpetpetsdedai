#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Camera.h"
#include "GravitySystem.h"
#include "BoxCollider.h"
#include "PhysicsEngine.h"
#include "GraphicDebugger.h"
#include "MyMath.h"
#include "GameScene.h"
#include "LevelOneScene.h"
#include "MenuScene.h"
#include "SceneManager.h"
#include "SingletonManager.h"
#include "TextureManager.h"

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

	std::shared_ptr<Scene> currentScene;
	sf::RenderWindow window;
};

