#include "../../Headers/Components/Button.h"

#include "../../Headers/Components/Camera.h"
#include "../../Headers/Components/SpriteRenderer.h"
#include "../../Headers/Engine/GameObject.h"
#include "../../Headers/Utilities/Utilities.h"

sf::Font Button::font;
bool Button::fontLoaded;
Button::Button() :camera(nullptr), isMousePressed(false), ClickOnTheButton(false), buttonState(ButtonState::Normal)
{
}

void Button::Init(std::shared_ptr<GameObject> _gameObject, std::string _buttonString, Camera* _camera)
{
	if (!fontLoaded)
	{
		if (!font.loadFromFile("./Fonts/Arial.ttf"))
		{
			std::cout << "ERROR" << std::endl;
		}
		else
		{
			fontLoaded = true;
		}

	}
	
	buttonText.setFont(font); // font is a sf::Font

	// set the character size
	buttonText.setCharacterSize(48); // in pixels, not points!
	buttonText.setStyle(sf::Text::Bold | sf::Text::Underlined);
	// set the color
	buttonText.setFillColor(sf::Color::Black);
	SetString(_buttonString);

	camera = _camera;
	camera->AddToTexts(&buttonText);

	spriteRenderer = _gameObject->AddComponent<SpriteRenderer>();
	spriteRenderer->SetSprite("RoundedRectangle");
	UpdatePosition();
}

void Button::SetString(std::string _buttonString)
{
	buttonText.setString(_buttonString);
	sf::FloatRect textRect = buttonText.getLocalBounds();
	buttonText.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
}

sf::Text* Button::GetText()
{
	return &buttonText;
}

bool Button::IsInButton(const sf::Vector2i& positionToCheck)
{
	if (!camera->IsOnDisplay(gameObject))
	{
		return false;
	}

	return Utilities::IsInBounds(sf::Vector2f(positionToCheck.x, positionToCheck.y),
	                             gameObject->GetPosition() - camera->GetAttachedObject()->GetPosition(),
	                             GetCurrentSize());
}

void Button::SetColor(const sf::Color& _color)
{
	spriteRenderer->SetColor(_color);
	buttonText.setFillColor(_color);
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
	mousePosition = sf::Mouse::getPosition(*camera->GetCurrentWindow());
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

sf::Vector2f Button::GetCurrentSize()
{
	return sf::Vector2f(
		spriteRenderer->GetSprite()->getTexture()->getSize().x * spriteRenderer->GetSprite()->getScale().x,
		spriteRenderer->GetSprite()->getTexture()->getSize().y * spriteRenderer->GetSprite()->getScale().y
	);
}


void Button::UpdatePosition()
{ 
	sf::Vector2f newPos;
	if (spriteRenderer->GetSprite()->getTexture() != nullptr)
	{
		newPos.x = gameObject->GetPosition().x + ((spriteRenderer->GetSprite()->getTexture()->getSize().x * spriteRenderer->GetSprite()->getScale().x) / 2);
		newPos.y = gameObject->GetPosition().y + ((spriteRenderer->GetSprite()->getTexture()->getSize().y * spriteRenderer->GetSprite()->getScale().y) / 2);
	}
	else
	{
		newPos.x = gameObject->GetPosition().x + (spriteRenderer->GetSprite()->getScale().x / 2);
		newPos.y = gameObject->GetPosition().y + (spriteRenderer->GetSprite()->getScale().y / 2);
	}

	buttonText.setPosition(newPos);

	oldObjPosition = gameObject->GetPosition();
}

