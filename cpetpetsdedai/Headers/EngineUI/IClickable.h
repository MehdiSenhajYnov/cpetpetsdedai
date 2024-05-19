#pragma once
#include "../../EngineUI.h"
#include "../Utilities/Event.h"
#include "../Utilities/Utilities.h"
enum class ClickableState
{
    Normal,
    Hover,
    Pressed,
    Disabled
};
class IClickable
{
public:
    virtual ~IClickable() = default;
    // remind: need to be called to work
    virtual void Update(float _deltaTime);
protected:
    InBoundsInputType inBoundsInputType = TopLeft;
    virtual void InternalChangeColor(sf::Color _newColor);
    virtual void ChangeColor(sf::Color _newColor, ClickableState _newState) = 0;
    virtual sf::Vector2f GetClickablePosition() = 0;
    virtual sf::Vector2f GetClickableSize() = 0;
public:

    [[nodiscard]] ClickableState GetClickableState() const;
    void DisableIClickable();
	
    void SetBaseColor(const sf::Color& _color);
    void SetHoverColor(const sf::Color& _color);
    void SetPressedColor(const sf::Color& _color);
    void SetDisabledColor(const sf::Color& _color);

    void ClickMouse();

    Event<IClickable*> OnClick;
    
    Event<IClickable*> OnHover;
    Event<IClickable*> OnUnhover;
	
    Event<IClickable*> OnMouseEnter; 
    Event<IClickable*> OnMouseExit;
    Event<IClickable*> OnMouseClickDown;
    Event<IClickable*> OnMouseClickUp;

private:
    void OnMouseKeyDown();
    void OnMouseKeyUp();
    [[nodiscard]] bool IsInIClickable(const sf::Vector2f& positionToCheck);

    sf::Vector2f oldObjPosition;
    sf::Vector2f mousePosition;

    bool isMouseInside = false;
    bool isMousePressingTheClickable = false;
	
    bool isMousePressed = false;
    bool ClickOnTheClickable = false;
    bool isMouseHover = false;

    ClickableState tempState = ClickableState::Normal;
    ClickableState clickableState = ClickableState::Normal;

    sf::Color baseColor = sf::Color(0, 0, 0, 255);
    sf::Color hoverColor = sf::Color(110, 110, 110, 255);
    sf::Color pressedColor = sf::Color(80, 80, 80, 255);
    sf::Color disabledColor = sf::Color(30, 30, 30, 255);
	
    bool wantHoverColor = false;
    bool wantPressedColor = false;
    bool wantDisabledColor = false;

};
