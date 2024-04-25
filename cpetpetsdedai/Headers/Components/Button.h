#pragma once
#include "Component.h"
#include "Camera.h"
#include "SpriteRenderer.h"
#include "../Utilities/Event.h"
enum class ButtonState
{
	Normal,
	Hover,
	Pressed,
	Disabled
};

class Button : public Component
{
public:
	Button();
	void Init(std::shared_ptr<GameObject> _gameObject, std::string _buttonString, Camera* _camera);
	void SetString(std::string _buttonString);

	sf::Text* GetText();

	Event<Button*> OnButtonClicked;
	
	Event<Button*> OnMouseEnter; 
	Event<Button*> OnMouseExit;
	Event<Button*> OnMouseClickDown;
	Event<Button*> OnMouseClickUp;
	
	bool IsInButton(sf::Vector2i positionToCheck);

	void SetColor(sf::Color color);
	sf::Color GetColor();
	
	ButtonState GetButtonState();
	void DisableButton();
	// Hérité via Component
	void Start() override;
	void Update(float deltaTime) override;
private:
	static sf::Font font;
	static bool fontLoaded;

	void Logs(sf::Vector2i positionToCheck);
	void UpdatePosition();

	sf::Vector2f oldObjPosition;
	sf::Vector2i mousePosition;
	Camera* camera;
	sf::Text buttonText;

	bool isMousePressed;
	bool ClickOnTheButton;
	bool isMouseHover;

	ButtonState tempState;
	ButtonState buttonState;

	SpriteRenderer spriteRenderer;

};

