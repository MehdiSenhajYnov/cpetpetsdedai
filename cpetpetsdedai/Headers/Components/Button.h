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
	Event<Button*> OnButtonHover;
	Event<Button*> OnButtonUnHover;
	
	Event<Button*> OnMouseEnter; 
	Event<Button*> OnMouseExit;
	Event<Button*> OnMouseClickDown;
	Event<Button*> OnMouseClickUp;

	
	
	bool IsInButton(const sf::Vector2i& positionToCheck);

	void SetColor(const sf::Color& _color);
	sf::Color GetColor();
	
	ButtonState GetButtonState();
	void DisableButton();
	// Hérité via Component
	void Start() override;
	void Update(float _deltaTime) override;

	sf::Vector2f GetSize();
	sf::Vector2f GetCurrentSize();
private:
	static sf::Font font;
	static bool fontLoaded;

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

