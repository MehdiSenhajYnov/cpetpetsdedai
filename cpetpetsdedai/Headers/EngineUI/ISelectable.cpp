#include "ISelectable.h"
#include "../Input/Input.h"

void ISelectable::DisableISelectable()
{
	selectableState = SelectableState::Disabled;
	isMousePressed = false;
	ClickOnTheSelectable = false;
	isMousePressingTheSelectable = false;
	ChangeColor(disabledColor, tempState);
}

void ISelectable::Update(float _deltaTime)
{
	if (selectableState == SelectableState::Disabled)
	{
		return;
	}
	mousePosition = Input::GetMousePosition();
	
	isMouseInside = IsInISelectable(mousePosition);
	if (isMouseInside)
	{
		if (!isMouseHover)
		{
			OnMouseEnter.InvokeEvent(this);
			if (selectableState != SelectableState::Pressed && selectableState != SelectableState::Selected)
			{
				tempState = SelectableState::Hover;
				OnISelectableHover.InvokeEvent(this);
			}
		}
		isMouseHover = true;
	} 
	else
	{
		if (isMouseHover)
		{
			if (selectableState != SelectableState::Pressed && selectableState != SelectableState::Selected)
			{
				tempState = SelectableState::Normal;
				OnISelectableUnHover.InvokeEvent(this);
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
		ClickOnTheSelectable = false;
		isMousePressed = false;
		isMousePressingTheSelectable = false;
	}
	
	selectableState = tempState;
	InternalChangeColor(baseColor);
}

void ISelectable::Select()
{
	tempState = SelectableState::Selected;
	OnSelect.InvokeEvent(this);
	InternalChangeColor(selectedColor);
}

void ISelectable::Deselect()
{
	if (selectableState != SelectableState::Selected) return;
	tempState = SelectableState::Normal;
	OnDeselect.InvokeEvent(this);
	InternalChangeColor(baseColor);
}

void ISelectable::InternalChangeColor(sf::Color _newColor)
{
	
	if (selectableState == SelectableState::Normal)
	{
		ChangeColor(baseColor, tempState);
	}
	else if (selectableState == SelectableState::Hover && wantHoverColor)
	{
		ChangeColor(hoverColor, tempState);
	}
	else if (selectableState == SelectableState::Pressed && wantPressedColor)
	{
		ChangeColor(pressedColor, tempState);
	} else if (selectableState == SelectableState::Selected && wantSelectedColor)
	{
		ChangeColor(selectedColor, tempState);
	} else if (selectableState == SelectableState::Disabled && wantDisabledColor)
	{
		ChangeColor(disabledColor, tempState);
	}
	
}

SelectableState ISelectable::GetSelectableState() const
{
	return selectableState;
}

void ISelectable::OnMouseKeyDown()
{
	if (isMouseHover)
	{
		isMousePressingTheSelectable = true;
		ClickOnTheSelectable = true;
		tempState = SelectableState::Pressed;
		OnMouseClickDown.InvokeEvent(this);
	} else
	{
		Deselect();
	}
}

void ISelectable::OnMouseKeyUp()
{
	if (isMouseHover)
	{
		if (ClickOnTheSelectable)
		{
			Select();
		}
	}
	OnMouseClickUp.InvokeEvent(this);
}

void ISelectable::SetBaseColor(const sf::Color& _color)
{
	baseColor = _color;
	if (selectableState == SelectableState::Normal)
	{
		ChangeColor(_color, tempState);
	}
}

void ISelectable::SetHoverColor(const sf::Color& _color)
{
	hoverColor = _color;
	if (selectableState == SelectableState::Hover)
	{
		ChangeColor(_color, tempState);
	}
	wantHoverColor = true;
}

void ISelectable::SetPressedColor(const sf::Color& _color)
{
	pressedColor = _color;
	if (selectableState == SelectableState::Pressed)
	{
		ChangeColor(_color, tempState);
	}
	wantPressedColor = true;
}

void ISelectable::SetSelectedColor(const sf::Color& _color)
{
	selectedColor = _color;
	if (selectableState == SelectableState::Selected)
	{
		ChangeColor(_color, tempState);
	}
	wantSelectedColor = true;
}

void ISelectable::SetDisabledColor(const sf::Color& _color)
{
	selectedColor = _color;
	if (selectableState == SelectableState::Disabled)
	{
		ChangeColor(_color, tempState);
	}
	wantDisabledColor = true;
}

bool ISelectable::IsInISelectable(const sf::Vector2f& positionToCheck)
{
	return Utilities::IsInBounds(mousePosition, GetSelectablePosition(), GetSelectableSize(), inBoundsInputType);
}
