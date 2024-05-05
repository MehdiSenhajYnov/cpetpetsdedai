#include <iostream>
#include "../../Headers/Scenes/MenuScene.h"
#include "../../Headers/Engine/GameObject.h"
#include "../../Headers/Scenes/SceneManager.h"
#include "../../Headers/Components/Button.h"
#include "../../Headers/Utilities/Event.h"
#include "../../Headers/Components/SpriteRenderer.h"
#include "../../TextComponent.h"

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

	playButtonObj = CreateGameObjectImmediate("playButton");
	exitButtonObj = CreateGameObjectImmediate("exitButton");
	
	playButtonObj->SetPosition(window->getSize().x / 2, window->getSize().y / 2 - 50);

	playButtonComponent = playButtonObj->AddComponent<Button>();
	playButtonComponent->InitDefaultButton("PLAY");
	playButtonComponent->OnButtonClicked.Subscribe(&MenuScene::OnPlayButtonClicked, this);
	
	
	exitButtonObj->SetPosition(window->getSize().x / 2, window->getSize().y / 2 + 50);

	exitButtonComponent = exitButtonObj->AddComponent<Button>();
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
	if (pressedKey == sf::Keyboard::Key::Space)
	{
		std::cout << "Space pressed, nb of fields : " << playButtonObj->GetType()->GetAllFields().size() << std::endl;
		for (auto& _field : playButtonObj->GetType()->GetAllFields())
		{
			std::cout << "field name : " << _field->name << std::endl;
		}

	}
}
