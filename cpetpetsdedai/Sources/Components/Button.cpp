#include "../../Headers/Components/Button.h"

#include "../../CameraManager.h"
#include "../../RendererManager.h"
#include "../../Headers/Components/Camera.h"
#include "../../Headers/Components/SpriteRenderer.h"
#include "../../Headers/Engine/GameObject.h"
#include "../../Headers/Utilities/Utilities.h"
#include "../../TextComponent.h"


Button::Button() :isMousePressed(false), ClickOnTheButton(false), buttonState(ButtonState::Normal)
{
}

void Button::Init(SpriteRenderer* _spriteRenderer)
{
	buttonInitialized = true;
	spriteRenderer = _spriteRenderer;
}

sf::Vector2f operator/(const sf::Vector2f& _vectorToDivide, float _divideValue)
{
	return sf::Vector2f(_vectorToDivide.x / _divideValue, _vectorToDivide.y / _divideValue);
}

void Button::InitDefaultButton(std::string _buttonString)
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
	spriteRenderer->SetOrigin(GetSize()/2);
}

void Button::InitDefaultTextComponent(std::string _buttonString)
{
	textComponent = gameObject->AddComponent<TextComponent>();
	textComponent->Init(_buttonString);
}


void Button::SetString(std::string _buttonString)
{
	if (textComponent == nullptr)
	{
		InitDefaultButton(_buttonString);
		return;
	}
	textComponent->SetString(_buttonString);
}

sf::Text* Button::GetText()
{
	return &textComponent->Text;
}

bool Button::IsInButton(const sf::Vector2i& positionToCheck)
{
	if (!RendererManager::GetInstance()->isOnDisplay(spriteRenderer))
	{
		return false;
	}

	return Utilities::IsInBounds(sf::Vector2f(positionToCheck.x, positionToCheck.y),
	                             gameObject->GetPosition() - CameraManager::GetInstance()->GetMainCamera()->GetAttachedObject()->GetPosition(),
	                             GetSize(), Center);
}

void Button::SetColor(const sf::Color& _color)
{
	spriteRenderer->SetColor(_color);
	textComponent->SetColor(_color);
}

sf::Color Button::GetColor()
{
	return spriteRenderer->GetColor();
}

ButtonState Button::GetButtonState()
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
	mousePosition = sf::Mouse::getPosition(*CameraManager::GetInstance()->GetMainCamera()->GetCurrentWindow());
	if (oldObjPosition != gameObject->GetPosition())
	{
		UpdatePosition();
	}

	if (IsInButton(mousePosition))
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
			if (isMouseHover)
			{
				ClickOnTheButton = true;
				tempState = ButtonState::Pressed;
				OnMouseClickDown.InvokeEvent(this);
			}
		}
	}
	else
	{
		if (isMousePressed)
		{
			if (isMouseHover)
			{
				if (ClickOnTheButton)
				{
					OnButtonClicked.InvokeEvent(this);
				}
			}
			OnMouseClickUp.InvokeEvent(this);
		}
		if (tempState == ButtonState::Pressed)
		{
			tempState = ButtonState::Hover;
		}
		ClickOnTheButton = false;
		isMousePressed = false;
	}


	buttonState = tempState;
}

sf::Vector2f Button::GetSize()
{
	return spriteRenderer->GetSize();
}

SpriteRenderer* Button::GetSpriteRenderer()
{
	 return spriteRenderer;
}

void Button::UpdatePosition()
{ 
	sf::Vector2f newPos;
	if (spriteRenderer->GetSprite()->getTexture() != nullptr)
	{
		newPos.x = gameObject->GetPosition().x + ((GetSize().x * spriteRenderer->GetSprite()->getScale().x) / 2);
		newPos.y = gameObject->GetPosition().y + ((GetSize().y * spriteRenderer->GetSprite()->getScale().y) / 2);
	}
	else
	{
		newPos.x = gameObject->GetPosition().x + (spriteRenderer->GetSprite()->getScale().x / 2);
		newPos.y = gameObject->GetPosition().y + (spriteRenderer->GetSprite()->getScale().y / 2);
	}

	textComponent->setPosition(newPos);

	oldObjPosition = gameObject->GetPosition();
}

