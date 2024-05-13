#include "../../Headers/Engine/GameManager.h"

#include "../../EngineUI.h"
#include "../../RendererManager.h"
#include "../../Headers/GameSystem/SingletonManager.h"
#include "../../Headers/Input/Input.h"
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
	std::cout << "GameManager destroyed" << std::endl;
	DeleteScene();
}

void GameManager::Run()
{
	if (cursor.loadFromSystem(sf::Cursor::Arrow))
	{
		window.setMouseCursor(cursor);
	}

	Input::Init(&window);
	
	RendererManager::GetInstance()->Init(&window);
	SingletonManager singletonManager;
	singletonManager.InitAll();
	EngineUI::GetInstance()->Init(&window, &cursor);
	
	SceneManager::OnSceneChanged.Subscribe(&GameManager::OnChangeSceneAsked, this);
	haveToChangeScene = false;
	OnChangeSceneAsked(SceneManager::SceneEnum::Menu);

	sf::Clock dtClock;
	float deltaTime = 0;

	window.setKeyRepeatEnabled(false);
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
		Input::Clear();
		InputEvents();
		currentScene->BaseSceneUpdate(deltaTime);
		RendererManager::GetInstance()->DrawProcess();
	}

	DeleteScene();

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
		//currentScene = Factory::GetInstance()->CreateObject<MenuScene>();
	}
	else if (sceneToUse == SceneManager::SceneEnum::Level1)
	{
		//currentScene = Factory::GetInstance()->CreateObject<EditorScene>();
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
	//Factory::GetInstance()->DestroyObject(currentScene);
	currentScene->PreDestroy();
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
			Input::AddKeyDown(Input::FromSFKeyboard(event.key.code));
		}
		if (event.type == sf::Event::KeyReleased)
		{
			Input::AddKeyUp(Input::FromSFKeyboard(event.key.code));
		}
		
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (currentScene != nullptr && iswindowFocus)
			{
				currentScene->OnMouseKeyDown(event.mouseButton.button);
				Input::AddKeyDown(Input::FromSFMouse(event.mouseButton.button));
			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (currentScene != nullptr && iswindowFocus)
			{
				currentScene->OnMouseKeyUp(event.mouseButton.button);
				Input::AddKeyUp(Input::FromSFMouse(event.mouseButton.button));
			}
		}
		if (event.type == sf::Event::TextEntered)
		{
			if (std::isprint(static_cast<unsigned char>(event.text.unicode)))
			{
				Input::AddTextEntered(static_cast<char>(event.text.unicode));
			}
		}
				
	}
}

