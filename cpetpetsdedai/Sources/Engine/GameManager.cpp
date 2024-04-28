#include "../../Headers/Engine/GameManager.h"
#include "../../Headers/GameSystem/SingletonManager.h"
#include "../../Headers/Scenes/EditorScene.h"
#include "../../Headers/Scenes/MenuScene.h"
#include "../../Headers/Utilities/Event.h"
#include "../../Headers/Scenes/Scene.h"



GameManager::GameManager() :
window(sf::VideoMode(1700, 1000), "Simple 2D Game", sf::Style::Fullscreen)
{
	iswindowFocus = true;
}

GameManager::~GameManager()
{
	std::cout << "GameManager destroyed" << std::endl;
}

void GameManager::Run()
{
	SingletonManager singletonManager;
	singletonManager.InitAll();
	SceneManager::OnSceneChanged.Subscribe(&GameManager::OnChangeSceneAsked, this);
	haveToChangeScene = false;
	OnChangeSceneAsked(SceneManager::SceneEnum::Menu);

	sf::Clock dtClock;
	float deltaTime;

	while (window.isOpen())
	{
		if (haveToChangeScene)
		{
			ChangeScene(newScene);
		}
		WindowsEvents();
		if (!iswindowFocus) continue;

		deltaTime = dtClock.restart().asSeconds();
		currentScene->Update(deltaTime);
	}
	
}

void GameManager::OnChangeSceneAsked(SceneManager::SceneEnum sceneToUse)
{
	newScene = sceneToUse;
	haveToChangeScene = true;
}

void GameManager::ChangeScene(SceneManager::SceneEnum sceneToUse)
{
	if (sceneToUse == SceneManager::SceneEnum::Menu)
	{
		currentScene = std::make_unique<MenuScene>();
	}
	else if (sceneToUse == SceneManager::SceneEnum::Level1)
	{
		currentScene = std::make_unique<EditorScene>();
	}

	currentScene->InitializeScene(&window);
	haveToChangeScene = false;

}






void GameManager::WindowsEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::GainedFocus)
		{
			iswindowFocus = true;
			std::cout << "window gained focus : " << std::endl;
		}

		if (event.type == sf::Event::LostFocus)
		{
			iswindowFocus = false;
			std::cout << "window lost focus : " << std::endl;
		}


		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				window.close();
			}

			if (currentScene != nullptr && iswindowFocus)
			{
				currentScene->OnKeyDown(event.key.code);
			}

		}
	}
}