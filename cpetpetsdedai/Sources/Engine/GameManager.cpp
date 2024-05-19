#include "../../Headers/Engine/GameManager.h"

#include "../../EngineUI.h"
#include "../../RendererManager.h"
#include "../../Headers/GameSystem/SingletonManager.h"
#include "../../Headers/Input/Input.h"
#include "../../Headers/Scenes/EditorScene.h"
#include "../../Headers/Scenes/MenuScene.h"
#include "../../Headers/Utilities/Event.h"
#include "../../Headers/Scenes/Scene.h"



GameManager::GameManager() :
                             //window(sf::VideoMode(1000, 500), "Simple 2D Game", sf::Style::Resize)
                             window(sf::VideoMode(1900, 1200), "Simple 2D Game", sf::Style::Default)
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

	Input::Init(&window);
	
	RendererManager::GetInstance()->Init(&window);
	SingletonManager singletonManager;
	singletonManager.InitAll();
	EngineUI::GetInstance()->Init(&window);
	
	SceneManager::GetInstance()->OnSceneChanged.Subscribe(&GameManager::OnChangeSceneAsked, this);
	haveToChangeScene = false;
	OnChangeSceneAsked(SceneManager::SceneEnum::Menu);

	sf::Clock dtClock;

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
		RendererManager::GetInstance()->Clear();
		Input::Clear();
		InputEvents();
		SceneManager::GetInstance()->GetCurrentScene()->BaseSceneUpdate(dtClock.restart().asSeconds());
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
		SceneManager::GetInstance()->SetCurrentScene(new MenuScene());
		//currentSceneType = Factory::GetInstance()->CreateObject<MenuScene>();
	}
	else if (sceneToUse == SceneManager::SceneEnum::Level1)
	{
		//currentSceneType = Factory::GetInstance()->CreateObject<EditorScene>();
		SceneManager::GetInstance()->SetCurrentScene(new EditorScene());
	}

	//bool CreateScene = SceneManager::GetInstance()->GetCurrentScene()->sceneFileEditor.CreateNewScene();

	// if (!CreateScene)
	// {
	// } else
	// {
	// }

	
	SceneManager::GetInstance()->GetCurrentScene()->BaseInit(&window);

	SceneManager::GetInstance()->GetCurrentScene()->sceneFileEditor.LoadScene();
	
	// SceneManager::GetInstance()->GetCurrentScene()->AddMethods();
	// SceneManager::GetInstance()->GetCurrentScene()->InitializeScene(&window);
	
	haveToChangeScene = false;

}

void GameManager::DeleteScene()
{
	if (SceneManager::GetInstance()->GetCurrentScene() == nullptr)
	{
		return;
	}
	//Factory::GetInstance()->DestroyObject(currentSceneType);
	SceneManager::GetInstance()->GetCurrentScene()->PreDestroy();
	delete SceneManager::GetInstance()->GetCurrentScene();
	SceneManager::GetInstance()->SetCurrentScene(nullptr);
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
			window.setView(sf::View(sf::FloatRect(0, 0, (float)event.size.width, (float)event.size.height)));
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

			if (SceneManager::GetInstance()->GetCurrentScene() != nullptr && iswindowFocus)
			{
				SceneManager::GetInstance()->GetCurrentScene()->OnKeyDown(event.key.code);
			}
			Input::AddKeyDown(Input::FromSFKeyboard(event.key.code));
		}
		if (event.type == sf::Event::KeyReleased)
		{
			Input::AddKeyUp(Input::FromSFKeyboard(event.key.code));
		}
		
		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (SceneManager::GetInstance()->GetCurrentScene() != nullptr && iswindowFocus)
			{
				SceneManager::GetInstance()->GetCurrentScene()->OnMouseKeyDown(event.mouseButton.button);
				Input::AddKeyDown(Input::FromSFMouse(event.mouseButton.button));
			}
		}
		if (event.type == sf::Event::MouseButtonReleased)
		{
			if (SceneManager::GetInstance()->GetCurrentScene() != nullptr && iswindowFocus)
			{
				SceneManager::GetInstance()->GetCurrentScene()->OnMouseKeyUp(event.mouseButton.button);
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

