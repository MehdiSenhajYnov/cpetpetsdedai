#include "../../Headers/Components/Button.h"
#include "../../Headers/Engine/GameObject.h"
#include "../../Headers/Utilities/Utilities.h"

sf::Font Button::font;
bool Button::fontLoaded;

Button::Button() :camera(nullptr), isMousePressed(false), ClickOnTheButton(false), buttonState(ButtonState::Normal)
{
}

void Button::Init(std::shared_ptr<GameObject> _gameObject, std::string _buttonString, Camera* _camera)
{
	Component::Init(_gameObject);
	
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

	UpdatePosition();

	camera = _camera;
	camera->AddToTexts(&buttonText);

	spriteRenderer.SetSprite("RoundedRectangle");
	_gameObject->AddComponent(&spriteRenderer);
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

bool Button::IsInButton(sf::Vector2i positionToCheck)
{
	if (!camera->IsOnDisplay(gameObject.get()))
	{
		return false;
	}
	//if (gameObject->Name == "exitButton")
	//{
	//	Logs(positionToCheck);
	//}

	if (positionToCheck.x < (gameObject->GetPosition().x - camera->GetAttachedObject()->GetPosition().x))
	{
		return false;
	}

	if (positionToCheck.y < (gameObject->GetPosition().y - camera->GetAttachedObject()->GetPosition().y))
	{
		return false;
	}

	if (spriteRenderer.GetSprite()->getTexture() != nullptr)
	{
		if (positionToCheck.x > (gameObject->GetPosition().x - camera->GetAttachedObject()->GetPosition().x) +
			(spriteRenderer.GetSprite()->getTexture()->getSize().x * spriteRenderer.GetSprite()->getScale().x))
		{
			return false;

		}


		if (positionToCheck.y > (gameObject->GetPosition().y - camera->GetAttachedObject()->GetPosition().y) +
			(spriteRenderer.GetSprite()->getTexture()->getSize().y * spriteRenderer.GetSprite()->getScale().y))
		{
			return false;
		}

	}
	else
	{
		if (positionToCheck.x > (gameObject->GetPosition().x - camera->GetAttachedObject()->GetPosition().x) + spriteRenderer.GetSprite()->getScale().x)
		{
			return false;
		}

		if (positionToCheck.y > (gameObject->GetPosition().y - camera->GetAttachedObject()->GetPosition().y) + spriteRenderer.GetSprite()->getScale().y)
		{
			return false;
		}

	}
	return true;
}

void Button::SetColor(sf::Color color)
{
	spriteRenderer.SetColor(color);
	buttonText.setFillColor(color);
}

sf::Color Button::GetColor()
{
	return spriteRenderer.GetColor();
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

void Button::Logs(sf::Vector2i positionToCheck)
{
	std::cout << std::endl << std::endl << std::endl;
	std::cout << "mouse position : " << Utilities::VectorToString(sf::Vector2f(positionToCheck.x, positionToCheck.y)) << std::endl;
	std::cout << "gameObject position : " << Utilities::VectorToString(gameObject->GetPosition()) << std::endl;
	std::cout << "gameObjectWithCamereOffset position : " << Utilities::VectorToString(gameObject->GetPosition() - camera->GetAttachedObject()->GetPosition()) << std::endl;

	sf::Vector2f limits = gameObject->GetPosition() - camera->GetAttachedObject()->GetPosition();
	limits = limits + sf::Vector2f(
		spriteRenderer.GetSprite()->getTexture()->getSize().x * spriteRenderer.GetSprite()->getScale().x,
		spriteRenderer.GetSprite()->getTexture()->getSize().y * spriteRenderer.GetSprite()->getScale().y
	);

	std::cout << "limits : " << Utilities::VectorToString(limits) << std::endl;
	std::cout << std::endl << std::endl << std::endl;
}

void Button::Update(float deltaTime)
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
			tempState = ButtonState::Hover;
			isMouseHover = true;
			OnMouseEnter.InvokeEvent(this);
		}
	} 
	else if (isMouseHover)
	{
		if (buttonState != ButtonState::Pressed)
		{
			tempState = ButtonState::Normal;
		}
		isMouseHover = false;
		OnMouseExit.InvokeEvent(this);
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



void Button::UpdatePosition()
{
	sf::Vector2f newPos;
	if (spriteRenderer.GetSprite()->getTexture() != nullptr)
	{
		newPos.x = gameObject->GetPosition().x + ((spriteRenderer.GetSprite()->getTexture()->getSize().x * spriteRenderer.GetSprite()->getScale().x) / 2);
		newPos.y = gameObject->GetPosition().y + ((spriteRenderer.GetSprite()->getTexture()->getSize().y * spriteRenderer.GetSprite()->getScale().y) / 2);
	}
	else
	{
		newPos.x = gameObject->GetPosition().x + (spriteRenderer.GetSprite()->getScale().x / 2);
		newPos.y = gameObject->GetPosition().y + (spriteRenderer.GetSprite()->getScale().y / 2);
	}

	buttonText.setPosition(newPos);

	oldObjPosition = gameObject->GetPosition();
}

