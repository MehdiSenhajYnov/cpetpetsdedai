#include "IClickable.h"

#include "../Input/Input.h"

void IClickable::DisableIClickable()
{
	clickableState = ClickableState::Disabled;
	isMousePressed = false;
	ClickOnTheClickable = false;
	isMousePressingTheClickable = false;
	ChangeColor(disabledColor, tempState);
}

void IClickable::Update(float _deltaTime)
{
	if (clickableState == ClickableState::Disabled)
	{
		return;
	}
	mousePosition = Input::GetMousePosition();
	
	isMouseInside = IsInIClickable(mousePosition);
	if (isMouseInside)
	{
		if (!isMouseHover)
		{
			OnMouseEnter.InvokeEvent(this);
			if (clickableState != ClickableState::Pressed)
			{
				tempState = ClickableState::Hover;
				OnHover.InvokeEvent(this);
			}
		}
		isMouseHover = true;
	} 
	else
	{
		if (isMouseHover)
		{
			if (clickableState != ClickableState::Pressed)
			{
				tempState = ClickableState::Normal;
				OnUnhover.InvokeEvent(this);
			}
			OnMouseExit.InvokeEvent(this);
		}
		isMouseHover = false;
	}

	// New input system
	if (Input::GetKeyDown(KeyCode::LeftMouse))
	{
		isMousePressed = true;
		OnMouseKeyDown();
	}
	if (Input::GetKeyUp(KeyCode::LeftMouse))
	{
		isMousePressed = false;
		OnMouseKeyUp();
		ClickOnTheClickable = false;
		isMousePressed = false;
		isMousePressingTheClickable = false;
	}
	
	clickableState = tempState;
	InternalChangeColor(baseColor);
}

void IClickable::InternalChangeColor(sf::Color _newColor)
{
	
	if (clickableState == ClickableState::Normal)
	{
		ChangeColor(baseColor, tempState);
	}
	else if (clickableState == ClickableState::Hover && wantHoverColor)
	{
		ChangeColor(hoverColor, tempState);
	}
	else if (clickableState == ClickableState::Pressed && wantPressedColor)
	{
		ChangeColor(pressedColor, tempState);
	} else if (clickableState == ClickableState::Disabled && wantDisabledColor)
	{
		ChangeColor(disabledColor, tempState);
	}
	
}

ClickableState IClickable::GetClickableState() const
{
	return clickableState;
}

void IClickable::OnMouseKeyDown()
{
	if (isMouseHover)
	{
		isMousePressingTheClickable = true;
		ClickOnTheClickable = true;
		tempState = ClickableState::Pressed;
		OnMouseClickDown.InvokeEvent(this);
	}
}

void IClickable::OnMouseKeyUp()
{
	if (isMouseHover)
	{
		if (ClickOnTheClickable)
		{
			ClickMouse();
		}
		tempState = ClickableState::Hover;
	} else
	{
		tempState = ClickableState::Normal;
	}
	OnMouseClickUp.InvokeEvent(this);
}

void IClickable::ClickMouse()
{
	OnClick.InvokeEvent(this);
}

void IClickable::SetBaseColor(const sf::Color& _color)
{
	baseColor = _color;
	if (clickableState == ClickableState::Normal)
	{
		ChangeColor(_color, tempState);
	}
}

void IClickable::SetHoverColor(const sf::Color& _color)
{
	hoverColor = _color;
	if (clickableState == ClickableState::Hover)
	{
		ChangeColor(_color, tempState);
	}
	wantHoverColor = true;
}

void IClickable::SetPressedColor(const sf::Color& _color)
{
	pressedColor = _color;
	if (clickableState == ClickableState::Pressed)
	{
		ChangeColor(_color, tempState);
	}
	wantPressedColor = true;
}

void IClickable::SetDisabledColor(const sf::Color& _color)
{
	disabledColor = _color;
	if (clickableState == ClickableState::Disabled)
	{
		ChangeColor(_color, tempState);
	}
	wantDisabledColor = true;
}



bool IClickable::IsInIClickable(const sf::Vector2f& positionToCheck)
{
	return Utilities::IsInBounds(mousePosition, GetClickablePosition(), GetClickableSize(), inBoundsInputType);
}
