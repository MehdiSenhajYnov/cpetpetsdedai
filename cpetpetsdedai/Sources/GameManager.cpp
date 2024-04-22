#include "../Headers/GameManager.h"

#include "SingletonManager.h"
#include "../Headers/TextureManager.h"

GameManager::GameManager() :
window(sf::VideoMode(1700, 1000), "Simple 2D Game", sf::Style::Fullscreen)
{
	iswindowFocus = true;
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
		currentScene = std::make_unique<LevelOneScene>();
	}
	else if (sceneToUse == SceneManager::SceneEnum::Level2)
	{
		currentScene = std::make_unique<LevelTwoScene>();
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