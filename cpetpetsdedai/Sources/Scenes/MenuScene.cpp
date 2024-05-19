#include <iostream>
#include "../../Headers/Scenes/MenuScene.h"
#include "../../Headers/Engine/GameObject.h"
#include "../../Headers/Scenes/SceneManager.h"
#include "../../Headers/Components/Button.h"
#include "../../Headers/Utilities/Event.h"

MenuScene::MenuScene() : Scene("MenuScene", Scene::GetStaticType())
{


	//MethodContainer::AddFunction<MenuScene, void, Button*>("OnExitButtonClicked" + std::to_string(GetId()), &MenuScene::OnExitButtonClicked, this);
}

void MenuScene::OnPlayButtonClicked(Button* btn)
{
	std::cout << "PLAY clicked !" << std::endl;
	//loadingButtonComponent.SetString("Loading ...");
	SceneManager::GetInstance()->SetLevel(1);
	OnSceneChanged();
}

void MenuScene::OnExitButtonClicked(Button* btn)
{
	std::cout << "EXIT clicked !" << std::endl;
	window->close();
}


void MenuScene::InitializeScene(sf::RenderWindow* _window)
{
	Scene::InitializeScene(_window);

	GameObject* playButtonObj = nullptr;
	GameObject* exitButtonObj = nullptr;

	Button* playButtonComponent = nullptr;
	Button* exitButtonComponent = nullptr;
	
	playButtonObj = Create<GameObject>();
	playButtonObj->Init("playButton");
	
	exitButtonObj = Create<GameObject>();
	exitButtonObj->Init("exitButton");
	
	playButtonObj->SetPosition((float)window->getSize().x / 2, (float)window->getSize().y / 2 - 50);

	playButtonComponent = playButtonObj->AddComponent<Button>();
	playButtonComponent->InitDefaultButton("PLAY");
	
	//playButtonComponent->OnButtonClicked.Subscribe(&MenuScene::OnPlayButtonClicked, this);

	//MethodContainer::AddFunction<MenuScene, void, Button*>("OnPlayButtonClicked", &MenuScene::OnPlayButtonClicked, this);

	
	playButtonComponent->OnButtonClicked.SubscribeSerializable("OnPlayButtonClicked" + std::to_string(GetId()));
	
	exitButtonObj->SetPosition((float)window->getSize().x / 2, (float)window->getSize().y / 2 + 50);

	exitButtonComponent = exitButtonObj->AddComponent<Button>();
	exitButtonComponent->OnButtonClicked.SubscribeSerializable("OnExitButtonClicked" + std::to_string(GetId()));
	exitButtonComponent->InitDefaultButton("EXIT");
	exitButtonComponent->OnButtonClicked.Subscribe(&MenuScene::OnExitButtonClicked, this);

	playButtonComponent->SetBaseColor(normalButtonColor);
	exitButtonComponent->SetBaseColor(normalButtonColor);

	playButtonComponent->SetHoverColor(hoverButtonColor);
	exitButtonComponent->SetHoverColor(hoverButtonColor);

	playButtonComponent->SetPressedColor(pressedButtonColor);
	exitButtonComponent->SetPressedColor(pressedButtonColor);

	playButtonComponent->SetTextColor(textColor);
}

void MenuScene::OnSceneChanged()
{
	sceneChanged = true;
}

void MenuScene::DestroyScene()
{

}

void MenuScene::OnKeyDown(sf::Keyboard::Key pressedKey)
{

}

void MenuScene::AddMethods()
{
	SERIALIZE_METHOD(MenuScene, void, OnPlayButtonClicked, Button*)
	SERIALIZE_METHOD(MenuScene, void, OnExitButtonClicked, Button*)
}
