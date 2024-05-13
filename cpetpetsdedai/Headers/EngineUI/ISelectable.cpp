#include "ISelectable.h"
#include "../Input/Input.h"

void ISelectable::DisableISelectable()
{
	selectableState = SelectableState::Disabled;
	isMousePressed = false;
	ClickOnTheSelectable = false;
	isMousePressingTheSelectable = false;
	ChangeColor(disabledColor);
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
}

void ISelectable::Select()
{
	tempState = SelectableState::Selected;
	OnSelect.InvokeEvent(this);
	ChangeColor(selectedColor);
}

void ISelectable::Deselect()
{
	tempState = SelectableState::Normal;
	OnDeselect.InvokeEvent(this);
	ChangeColor(baseColor);
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
		ChangeColor(_color);
	}
}

void ISelectable::SetHoverColor(const sf::Color& _color)
{
	hoverColor = _color;
	if (selectableState == SelectableState::Hover)
	{
		ChangeColor(_color);
	}
	wantHoverColor = true;
}

void ISelectable::SetPressedColor(const sf::Color& _color)
{
	pressedColor = _color;
	if (selectableState == SelectableState::Pressed)
	{
		ChangeColor(_color);
	}
	wantPressedColor = true;
}

void ISelectable::SetSelectedColor(const sf::Color& _color)
{
	selectedColor = _color;
	if (selectableState == SelectableState::Selected)
	{
		ChangeColor(_color);
	}
	wantSelectedColor = true;
}

void ISelectable::SetDisabledColor(const sf::Color& _color)
{
	selectedColor = _color;
	if (selectableState == SelectableState::Disabled)
	{
		ChangeColor(_color);
	}
	wantDisabledColor = true;
}

bool ISelectable::IsInISelectable(const sf::Vector2f& positionToCheck)
{
	return Utilities::IsInBounds(mousePosition, GetSelectablePosition(), GetSelectableSize(), inBoundsInputType);
}
