﻿#include "TextComponent.h"

sf::Font TextComponent::font;
bool TextComponent::fontLoaded;

void TextComponent::Init()
{
	DrawableComponent::Init();
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

}

void TextComponent::Init(std::string _text)
{
	Init();
	Text.setFont(font);

	// in pixels, not points
	Text.setCharacterSize(48);
	Text.setStyle(sf::Text::Bold | sf::Text::Underlined);
	Text.setFillColor(sf::Color::Black);
	SetString(_text);
}

void TextComponent::SetString(std::string _buttonString)
{
	Text.setString(_buttonString);
	sf::FloatRect textRect = Text.getLocalBounds();
	Text.setOrigin(textRect.left + textRect.width / 2.0f,
		textRect.top + textRect.height / 2.0f);
}

void TextComponent::Start()
{
	
}

const sf::Drawable* TextComponent::GetDrawable()
{
	return &Text;
}

void TextComponent::setPosition(sf::Vector2f pos)
{
	Text.setPosition(pos);
}

sf::Vector2f TextComponent::GetSize()
{
	return {Text.getLocalBounds().width, Text.getLocalBounds().height};
}

sf::FloatRect TextComponent::GetBounds()
{
	return Text.getLocalBounds();
}

void TextComponent::SetColor(const sf::Color& _color)
{
	Text.setFillColor(_color);
}

sf::Color TextComponent::GetColor() const
{
	return Text.getFillColor();
}

void TextComponent::SetDrawScale(sf::Vector2f _drawScale)
{
	Text.setScale(_drawScale);
}
