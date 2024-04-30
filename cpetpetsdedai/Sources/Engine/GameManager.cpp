#include "../../Headers/Engine/GameManager.h"

#include "../../RendererManager.h"
#include "../../Headers/GameSystem/SingletonManager.h"
#include "../../Headers/Scenes/EditorScene.h"
#include "../../Headers/Scenes/MenuScene.h"
#include "../../Headers/Utilities/Event.h"
#include "../../Headers/Scenes/Scene.h"



GameManager::GameManager() :
//window(sf::VideoMode(1000, 500), "Simple 2D Game", sf::Style::Resize)
window(sf::VideoMode(800, 400), "Simple 2D Game", sf::Style::Fullscreen)
{
	iswindowFocus = true;
}

GameManager::~GameManager()
{
	std::cout << "GameManager destroyed" << '\n';
	delete currentScene;
}

void GameManager::Run()
{
	SingletonManager singletonManager;
	singletonManager.InitAll();
	RendererManager::GetInstance()->Init(&window);
	
	SceneManager::OnSceneChanged.Subscribe(&GameManager::OnChangeSceneAsked, this);
	haveToChangeScene = false;
	OnChangeSceneAsked(SceneManager::SceneEnum::Menu);

	sf::Clock dtClock;
	float deltaTime = 0;

	while (window.isOpen())
	{
		if (haveToChangeScene)
		{
			ChangeScene(newScene);
		}
		WindowsEvents();
		if (!iswindowFocus) continue;

		deltaTime = dtClock.restart().asSeconds();

		RendererManager::GetInstance()->Clear();
		currentScene->Update(deltaTime);
		RendererManager::GetInstance()->Draw();
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
		currentScene = new MenuScene();
	}
	else if (sceneToUse == SceneManager::SceneEnum::Level1)
	{
		currentScene = new EditorScene();
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
		if (event.type == sf::Event::KeyPressed)
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
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (currentScene != nullptr && iswindowFocus)
			{
				currentScene->OnMouseKeyDown(event.mouseButton.button);
			}
		}
		
	}
}