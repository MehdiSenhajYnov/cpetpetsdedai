#include "../../Headers/Components/Button.h"
#include "../../CameraManager.h"
#include "../../RendererManager.h"
#include "../../Headers/Components/Camera.h"
#include "../../Headers/Components/SpriteRenderer.h"
#include "../../Headers/Engine/GameObject.h"
#include "../../Headers/Utilities/Utilities.h"
#include "../../TextComponent.h"

Button::Button() : Component("Button", Component::GetStaticType())
{
	SERIALIZE_FIELD(baseColor)
	SERIALIZE_FIELD(hoverColor)
	SERIALIZE_FIELD(pressedColor)
	SERIALIZE_FIELD(textColor)
	SERIALIZE_FIELD(wantHoverColor)
	SERIALIZE_FIELD(wantPressedColor)
	
	SERIALIZE_FIELD(spriteRenderer)
	SERIALIZE_FIELD(textComponent)
	SERIALIZE_FIELD(buttonInitialized)
	
	SERIALIZE_FIELD(OnButtonClicked)
	
}

void Button::Init(SpriteRenderer* _spriteRenderer)
{
	buttonInitialized = true;
	spriteRenderer = _spriteRenderer;
	spriteRenderer->SetZIndex(20);

}

void Button::InitDefaultButton(const std::string& _buttonString)
{
	buttonInitialized = true;

	InitDefaultSpriteRenderer();
	InitDefaultTextComponent(_buttonString);
	
	UpdatePosition();
}

void Button::InitDefaultSpriteRenderer()
{
	spriteRenderer = gameObject->AddComponent<SpriteRenderer>();
	spriteRenderer->SetSprite("RoundedRectangle");
	spriteRenderer->SetZIndex(20);
}

void Button::InitDefaultTextComponent(const std::string& _buttonString)
{
	textComponent = gameObject->AddComponent<TextComponent>();
	textComponent->Init(_buttonString);
}


void Button::SetString(const std::string& _buttonString)
{
	if (textComponent == nullptr)
	{
		InitDefaultButton(_buttonString);
		return;
	}
	textComponent->SetString(_buttonString);
}

TextComponent* Button::GetTextComponent() const
{
	return textComponent;
}

bool Button::IsInButton(const sf::Vector2i& positionToCheck) const
{
	if (spriteRenderer == nullptr)
	{
		return false;
	}
	if (gameObject == nullptr)
	{
		return false;
	}
	if (CameraManager::GetInstance()->GetMainCamera() == nullptr)
	{
		return false;
	}
	if (CameraManager::GetInstance()->GetMainCamera()->GetAttachedObject() == nullptr)
	{
		return false;
	}
	return Utilities::IsInBounds(sf::Vector2f(positionToCheck.x, positionToCheck.y),
	                             gameObject->GetPosition() - CameraManager::GetInstance()->GetMainCamera()->GetAttachedObject()->GetPosition() + spriteRenderer->GetOffsetPosition(),
	                             spriteRenderer->GetCurrentSize(), Center);
}


ButtonState Button::GetButtonState() const
{
	return buttonState;
}

void Button::DisableButton()
{
	buttonState = ButtonState::Disabled;
	isMousePressed = false;
	ClickOnTheButton = false;
}

void Button::Start()
{
}


void Button::Update(float _deltaTime)
{
	if (!buttonInitialized)
	{
		return;
	}
	mousePosition = sf::Mouse::getPosition(*RendererManager::GetInstance()->GetWindow());
	
	UpdatePosition();
	
	isMouseInside = IsInButton(mousePosition);
	if (isMouseInside)
	{
		if (!isMouseHover)
		{
			OnMouseEnter.InvokeEvent(this);
			if (buttonState != ButtonState::Pressed)
			{
				tempState = ButtonState::Hover;
				OnButtonHover.InvokeEvent(this);
			}
		}
		isMouseHover = true;
	} 
	else
	{
		if (isMouseHover)
		{
			if (buttonState != ButtonState::Pressed)
			{
				tempState = ButtonState::Normal;
				OnButtonUnHover.InvokeEvent(this);
			}
			OnMouseExit.InvokeEvent(this);
		}
		isMouseHover = false;
	}

	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (!isMousePressed)
		{
			isMousePressed = true;
			OnMouseKeyDown();
		}
	}
	else
	{
		if (isMousePressed)
		{
			isMousePressed = false;
			OnMouseKeyUp();
		}
		
		ClickOnTheButton = false;
		isMousePressed = false;
		isMousePressingTheButton = false;
	}


	
	buttonState = tempState;
	UpdateColor();
}

void Button::OnMouseKeyDown()
{
	if (isMouseHover)
	{
		isMousePressingTheButton = true;
		ClickOnTheButton = true;
		tempState = ButtonState::Pressed;
		OnMouseClickDown.InvokeEvent(this);
	}
}

void Button::OnMouseKeyUp()
{
	if (isMouseHover)
	{
		if (ClickOnTheButton)
		{
			OnButtonClicked.InvokeEvent(this);
		}
	}

	if (isMouseInside)
	{
		tempState = ButtonState::Hover;
	} 
	else
	{
		tempState = ButtonState::Normal;
	}

	OnMouseClickUp.InvokeEvent(this);
}


SpriteRenderer* Button::GetSpriteRenderer() const
{
	 return spriteRenderer;
}

void Button::UpdatePosition()
{ 
	sf::Vector2f newPos = spriteRenderer->GetOffsetPosition();
	UpdateTextComponentPosition(newPos);
	oldObjPosition = gameObject->GetPosition();
}

sf::Vector2f Button::GetNewPos() const
{
	if (spriteRenderer == nullptr)
	{
		return gameObject->GetPosition();
	}
	sf::Vector2f newPos;
	if (spriteRenderer->GetSprite()->getTexture() != nullptr)
	{
		newPos.x = gameObject->GetPosition().x + (spriteRenderer->GetCurrentSize().x/ 2);
		newPos.y = gameObject->GetPosition().y + (spriteRenderer->GetCurrentSize().y/ 2);
	}
	else
	{
		newPos.x = gameObject->GetPosition().x + (spriteRenderer->GetSprite()->getScale().x / 2);
		newPos.y = gameObject->GetPosition().y + (spriteRenderer->GetSprite()->getScale().y / 2);
	}
	
	return newPos;
}

void Button::UpdateTextComponentPosition(sf::Vector2f _newPos) const
{
	if (textComponent == nullptr)
	{
		return;
	}
	textComponent->SetOffsetPosition(_newPos);
}

void Button::UpdateColor() const
{
	if (spriteRenderer == nullptr)
	{
		return;
	}

	if (buttonState == ButtonState::Normal)
	{
		spriteRenderer->SetColor(baseColor);
	}
	else if (buttonState == ButtonState::Hover && wantHoverColor)
	{
		spriteRenderer->SetColor(hoverColor);
	}
	else if (buttonState == ButtonState::Pressed && wantPressedColor)
	{
		spriteRenderer->SetColor(pressedColor);
	}
	
}

void Button::SetSpriteRendererColor(const sf::Color& _color) const
{
	spriteRenderer->SetColor(_color);
}

void Button::SetBaseColor(const sf::Color& _color)
{
	baseColor = _color;
	if (buttonState == ButtonState::Normal)
	{
		spriteRenderer->SetColor(_color);
	}
}

void Button::SetHoverColor(const sf::Color& _color)
{
	hoverColor = _color;
	if (buttonState == ButtonState::Hover)
	{
		spriteRenderer->SetColor(_color);
	}
	wantHoverColor = true;
}

void Button::SetPressedColor(const sf::Color& _color)
{
	pressedColor = _color;
	if (buttonState == ButtonState::Pressed)
	{
		spriteRenderer->SetColor(_color);
	}
	wantPressedColor = true;
}

void Button::SetTextColor(const sf::Color& _color)
{
	textColor = _color;
	textComponent->SetColor(_color);
}
