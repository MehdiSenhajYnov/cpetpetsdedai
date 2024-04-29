#include <iostream>
#include "../../Headers/Scenes/MenuScene.h"
#include "../../Headers/Engine/GameObject.h"
#include "../../Headers/Scenes/SceneManager.h"
#include "../../Headers/Components/Button.h"
#include "../../Headers/Utilities/Event.h"



void MenuScene::OnBtnMouseEnter(Button* btn)
{
	btn->SetColor(hoverButtonColor);
}
void MenuScene::OnBtnMouseExit(Button* btn)
{
	btn->SetColor(normalButtonColor);
}

void MenuScene::OnBtnMouseClickDown(Button* btn)
{
	std::cout << "Mouse click down" << std::endl;
	btn->SetColor(pressedButtonColor);
}

void MenuScene::OnBtnMouseClickUp(Button* btn)
{
	std::cout << "Mouse click up" << std::endl;
	if (btn->GetButtonState() != ButtonState::Hover)
	{
		btn->SetColor(normalButtonColor);
	}
	else
	{
		btn->SetColor(hoverButtonColor);
	}
}


void MenuScene::OnPlayButtonClicked(Button* btn)
{
	std::cout << "PLAY clicked !" << std::endl;
	//loadingButtonComponent.SetString("Loading ...");
	SceneManager::SetLevel(1);
	OnSceneChanged();
}

void MenuScene::OnExitButtonClicked(Button* btn)
{
	std::cout << "EXIT clicked !" << std::endl;
	window->close();
}

void MenuScene::Update(float deltaTime)
{
	GameLoop(deltaTime);

	//std::cout << "drawing" << std::endl;
}

MenuScene::MenuScene() : Scene("MenuScene", Scene::GetStaticType())
{
}

void MenuScene::GameLoop(float deltaTime)
{
	CalUpdateOnAll(deltaTime);
}



void MenuScene::InitializeScene(sf::RenderWindow* _window)
{
	Scene::InitializeScene(_window);

	playButtonObj = CreateGameObject("playButton", 10);
	exitButtonObj = CreateGameObject("exitButton", 10);
	
	playButtonObj->SetPosition(window->getSize().x / 2, window->getSize().y / 2 - 50);

	playButtonComponent = playButtonObj->AddComponent<Button>();
	playButtonComponent->Init("PLAY", mainCamera);
	playButtonComponent->OnButtonClicked.Subscribe(&MenuScene::OnPlayButtonClicked, this);
	
	
	exitButtonObj->SetPosition(window->getSize().x / 2, window->getSize().y / 2 + 50);

	exitButtonComponent = exitButtonObj->AddComponent<Button>();
	exitButtonComponent->Init("EXIT", mainCamera);
	exitButtonComponent->OnButtonClicked.Subscribe(&MenuScene::OnExitButtonClicked, this);


	// LoadingObj = CreateGameObject("Loading", 10);
	// LoadingObj->SetPosition(playButtonObj->GetPosition().x + 105, playButtonObj->GetPosition().y - 40);
	//
	// loadingButtonComponent.Init(LoadingObj, "", &mainCamera);
	// LoadingObj->AddComponent(&loadingButtonComponent);

	playButtonComponent->SetColor(normalButtonColor);
	exitButtonComponent->SetColor(normalButtonColor);

	playButtonComponent->OnButtonHover.Subscribe(&MenuScene::OnBtnMouseEnter, this);
	playButtonComponent->OnButtonUnHover.Subscribe(&MenuScene::OnBtnMouseExit, this);
	playButtonComponent->OnMouseClickDown.Subscribe(&MenuScene::OnBtnMouseClickDown, this);
	playButtonComponent->OnMouseClickUp.Subscribe(&MenuScene::OnBtnMouseClickUp, this);
	exitButtonComponent->OnButtonHover.Subscribe(&MenuScene::OnBtnMouseEnter, this);
	exitButtonComponent->OnButtonUnHover.Subscribe(&MenuScene::OnBtnMouseExit, this);
	exitButtonComponent->OnMouseClickDown.Subscribe(&MenuScene::OnBtnMouseClickDown, this);
	exitButtonComponent->OnMouseClickUp.Subscribe(&MenuScene::OnBtnMouseClickUp, this);
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
