#pragma once
#include <SFML/Graphics/Text.hpp>

#include "Component.h"
#include "../Utilities/Event.h"

class TextComponent;
class SpriteRenderer;
class Camera;

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

	void Init(SpriteRenderer* _spriteRenderer);
	void InitDefaultButton(std::string _buttonString);
	void InitDefaultSpriteRenderer();
	void InitDefaultTextComponent(std::string _buttonString);


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

	SpriteRenderer* GetSpriteRenderer();
	
private:
	bool buttonInitialized;
	void UpdatePosition();

	sf::Vector2f oldObjPosition;
	sf::Vector2i mousePosition;

	bool isMousePressed;
	bool ClickOnTheButton;
	bool isMouseHover;

	ButtonState tempState;
	ButtonState buttonState;

	SpriteRenderer* spriteRenderer;
	TextComponent* textComponent;
};

