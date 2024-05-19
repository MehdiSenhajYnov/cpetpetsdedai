#pragma once
#include "Scene.h"

class Button;

class MenuScene : public Scene
{
public:
	ADD_TYPE(MenuScene, Scene, REG_TYPE)
	MenuScene();
	
private:



	//GameObject* LoadingObj;
	//Button loadingButtonComponent;


	void OnPlayButtonClicked(Button* btn);
	void OnExitButtonClicked(Button* btn);

	// Hérité via Scene
	void InitializeScene(sf::RenderWindow* _window) override;
	void OnSceneChanged();

	void DestroyScene() override;
	void OnKeyDown(sf::Keyboard::Key pressedKey) override;

public:
	void AddMethods() override;

private:
	sf::Color normalButtonColor = sf::Color(0, 0, 0);
	sf::Color hoverButtonColor = sf::Color(110, 110, 110);
	sf::Color pressedButtonColor = sf::Color(80, 80, 80);
	sf::Color textColor = sf::Color(0, 0, 0);

};

