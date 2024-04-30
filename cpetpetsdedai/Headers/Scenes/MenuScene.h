#pragma once
#include "Scene.h"

class Button;

class MenuScene : public Scene
{
public:
	MenuScene();
	AddType(MenuScene, Scene::GetStaticType())
	
	void GameLoop(float deltaTime);

private:
	GameObject* playButtonObj;
	GameObject* exitButtonObj;

	Button* playButtonComponent;
	Button* exitButtonComponent;


	//GameObject* LoadingObj;
	//Button loadingButtonComponent;


	void OnBtnMouseEnter(Button* btn);
	void OnBtnMouseExit(Button* btn);
	void OnBtnMouseClickDown(Button* btn);
	void OnBtnMouseClickUp(Button* btn);
	
	void OnPlayButtonClicked(Button* btn);
	void OnExitButtonClicked(Button* btn);

	// Hérité via Scene
	void Update(float deltaTime) override;
	void InitializeScene(sf::RenderWindow* _window) override;
	void OnSceneChanged();

	void DestroyScene() override;
	void OnKeyDown(sf::Keyboard::Key pressedKey) override;

	const sf::Color normalButtonColor = sf::Color(0, 0, 0);
	const sf::Color hoverButtonColor = sf::Color(110, 110, 110);
	const sf::Color pressedButtonColor = sf::Color(80, 80, 80);
	
};

