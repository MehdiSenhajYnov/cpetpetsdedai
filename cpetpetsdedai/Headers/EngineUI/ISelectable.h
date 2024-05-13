#pragma once
#include "../../EngineUI.h"
#include "../Utilities/Event.h"

enum class SelectableState
{
	Normal,
	Hover,
	Pressed,
	Selected,
	Disabled
};

class ISelectable
{
public:
	virtual ~ISelectable() = default;
	// remind: need to be called to work
    virtual void Update(float _deltaTime);
	void Select();
	void Deselect();
protected:
	InBoundsInputType inBoundsInputType = TopLeft;
	virtual void ChangeColor(sf::Color _newColor) = 0;
	virtual sf::Vector2f GetSelectablePosition() = 0;
	virtual sf::Vector2f GetSelectableSize() = 0;
public:

    [[nodiscard]] SelectableState GetSelectableState() const;
    void DisableISelectable();
	
    void SetBaseColor(const sf::Color& _color);
    void SetHoverColor(const sf::Color& _color);
    void SetPressedColor(const sf::Color& _color);
	void SetSelectedColor(const sf::Color& _color);

	void SetDisabledColor(const sf::Color& _color);

	Event<ISelectable*> OnSelect;
	Event<ISelectable*> OnDeselect;
	
	Event<ISelectable*> OnISelectableHover;
	Event<ISelectable*> OnISelectableUnHover;
	
	Event<ISelectable*> OnMouseEnter; 
	Event<ISelectable*> OnMouseExit;
	Event<ISelectable*> OnMouseClickDown;
	Event<ISelectable*> OnMouseClickUp;

private:
    void OnMouseKeyDown();
    void OnMouseKeyUp();
    [[nodiscard]] bool IsInISelectable(const sf::Vector2f& positionToCheck);

	sf::Vector2f oldObjPosition;
	sf::Vector2f mousePosition;

	bool isMouseInside = false;
	bool isMousePressingTheSelectable = false;
	
	bool isMousePressed = false;
	bool ClickOnTheSelectable = false;
	bool isMouseHover = false;

	SelectableState tempState = SelectableState::Normal;
	SelectableState selectableState = SelectableState::Normal;

	sf::Color baseColor = sf::Color(0, 0, 0);
	sf::Color hoverColor = sf::Color(110, 110, 110);
	sf::Color pressedColor = sf::Color(80, 80, 80);
	sf::Color selectedColor = sf::Color(50, 50, 50);
	sf::Color disabledColor = sf::Color(30, 30, 30);
	
	bool wantHoverColor = false;
	bool wantPressedColor = false;
	bool wantSelectedColor = false;
	bool wantDisabledColor = false;

};

