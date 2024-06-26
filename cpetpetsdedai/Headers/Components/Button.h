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
	ADD_TYPE(Button, Component, REG_TYPE)
	Button();

	void Init(SpriteRenderer* _spriteRenderer);
	void InitDefaultButton(const std::string& _buttonString);
	void InitDefaultSpriteRenderer();
	void InitDefaultTextComponent(const std::string& _buttonString);

	void Start() override;
	void Update(float _deltaTime) override;
	
	void DisableButton();

	[[nodiscard]] bool IsInButton(const sf::Vector2i& positionToCheck) const;

	[[nodiscard]] ButtonState GetButtonState() const;
	[[nodiscard]] SpriteRenderer* GetSpriteRenderer() const;
	[[nodiscard]] TextComponent* GetTextComponent() const;
	
	void SetString(const std::string& _buttonString);
	void SetBaseColor(const sf::Color& _color);
	void SetHoverColor(const sf::Color& _color);
	void SetPressedColor(const sf::Color& _color);
	void SetTextColor(const sf::Color& _color);

private:
	void OnMouseKeyDown();
	void OnMouseKeyUp();

	
	void UpdatePosition();
	void UpdateTextComponentPosition(sf::Vector2f _newPos) const;
	void UpdateColor() const;
	
	void SetSpriteRendererColor(const sf::Color& _color) const;
	[[nodiscard]] sf::Vector2f GetNewPos() const;
	
public:
	Event<Button*> OnButtonClicked;
	Event<Button*> OnButtonHover;
	Event<Button*> OnButtonUnHover;
	
	Event<Button*> OnMouseEnter; 
	Event<Button*> OnMouseExit;
	Event<Button*> OnMouseClickDown;
	Event<Button*> OnMouseClickUp;
private:
	bool buttonInitialized = false;

	sf::Vector2f oldObjPosition = sf::Vector2f(0, 0);
	sf::Vector2i mousePosition = sf::Vector2i(0, 0);

	bool isMouseInside = false;
	bool isMousePressingTheButton = false;
	
	bool isMousePressed = false;
	bool ClickOnTheButton = false;
	bool isMouseHover = false;

	ButtonState tempState = ButtonState::Normal;
	ButtonState buttonState = ButtonState::Normal;

	SpriteRenderer* spriteRenderer = nullptr;
	TextComponent* textComponent = nullptr;

	sf::Color baseColor = sf::Color(0, 0, 0);
	sf::Color hoverColor = sf::Color(110, 110, 110);
	sf::Color pressedColor = sf::Color(80, 80, 80);
	sf::Color textColor = sf::Color::White;
	
	bool wantHoverColor = false;
	bool wantPressedColor = false;
};

