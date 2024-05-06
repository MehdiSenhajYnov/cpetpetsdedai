#include "../../Headers/Engine/GameManager.h"

#include "../../RendererManager.h"
#include "../../Headers/GameSystem/SingletonManager.h"
#include "../../Headers/Scenes/EditorScene.h"
#include "../../Headers/Scenes/MenuScene.h"
#include "../../Headers/Utilities/Event.h"
#include "../../Headers/Scenes/Scene.h"



GameManager::GameManager() : newScene(), haveToChangeScene(false), currentScene(nullptr),
                             //window(sf::VideoMode(1000, 500), "Simple 2D Game", sf::Style::Resize)
                             window(sf::VideoMode(1500, 900), "Simple 2D Game", sf::Style::Default)
{
	iswindowFocus = true;
}

GameManager::~GameManager()
{
	std::cout << "GameManager destroyed" << '\n';
	DeleteScene();
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
		eventsOfTick.clear();
		WindowsEvents();
		if (!iswindowFocus) continue;
		if (haveToChangeScene)
		{
			ChangeScene(newScene);
		}
		deltaTime = dtClock.restart().asSeconds();
		RendererManager::GetInstance()->Clear();
		InputEvents();
		currentScene->Update(deltaTime);
		RendererManager::GetInstance()->Draw();
	}
	if (currentScene != nullptr)
	{
	    DeleteScene();
	}
}



void GameManager::OnChangeSceneAsked(SceneManager::SceneEnum sceneToUse)
{
	newScene = sceneToUse;
	haveToChangeScene = true;
}

void GameManager::ChangeScene(SceneManager::SceneEnum sceneToUse)
{
	DeleteScene();
	
	if (sceneToUse == SceneManager::SceneEnum::Menu)
	{
		currentScene = new MenuScene();
	}
	else if (sceneToUse == SceneManager::SceneEnum::Level1)
	{
		currentScene = new EditorScene();
	}

	bool CreateScene = currentScene->sceneFileEditor.CreateNewScene();
	// if (!CreateScene)
	// {
	// 	 currentScene->sceneFileEditor.LoadScene();
	// } else
	// {
	// }
	currentScene->InitializeScene(&window);
	haveToChangeScene = false;

}

void GameManager::DeleteScene()
{
	if (currentScene == nullptr)
	{
		return;
	}
	currentScene->PreDestroy();
	currentScene->DestroyScene();
	delete currentScene;
	currentScene = nullptr;
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
		} else if (event.type == sf::Event::LostFocus)
		{
			iswindowFocus = false;
			std::cout << "window lost focus : " << std::endl;
		} else if (event.type == sf::Event::Closed)
		{
			window.close();
		} else if(event.type == sf::Event::Resized)
		{
			window.setView(sf::View(sf::FloatRect(0, 0, event.size.width, event.size.height)));
		}
		else
		{
			eventsOfTick.push_back(event);
		}

	}
}

void GameManager::InputEvents()
{
	for (auto& event : eventsOfTick)
	{
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

