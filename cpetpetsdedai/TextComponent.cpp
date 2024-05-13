#include "TextComponent.h"

sf::Font TextComponent::font;
bool TextComponent::fontLoaded;

TextComponent::TextComponent() : TextComponent("TextComponent", DrawableComponent::GetStaticType())
{
}

TextComponent::TextComponent(const std::string& _typeName, Type* parentType): DrawableComponent(_typeName, parentType)
{
	SerializeField(std::string, currentText)
}


TextComponent::TextComponent(uint64_t _id): TextComponent(_id, "TextComponent", DrawableComponent::GetStaticType()) {}

TextComponent::TextComponent(const uint64_t& _id, const std::string& _name, Type* parentType): DrawableComponent(_id, _name, parentType)
{
	SerializeField(std::string, currentText)
}

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

void TextComponent::SetString(std::string _newTextString)
{
	currentText = _newTextString;
	Text.setString(_newTextString);
	// sf::FloatRect textRect = Text.getLocalBounds();
	// Text.setOrigin(textRect.left + textRect.width / 2.0f,
	// 	textRect.top + textRect.height / 2.0f);

	ResetOrigin();
}

std::string TextComponent::GetString() const
{
	return Text.getString();
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

sf::Vector2f TextComponent::GetOriginalSize()
{
	return {Text.getLocalBounds().width , Text.getLocalBounds().height};
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

sf::Vector2f TextComponent::GetCenter() const
{
	sf::FloatRect textRect = Text.getLocalBounds();
	return {textRect.left + textRect.width/2.0f,
				   textRect.top  + textRect.height/2.0f};
}



void TextComponent::SetFontSize(int _fontSize)
{
	Text.setCharacterSize(_fontSize);
	ResetOrigin();
}

void TextComponent::ResetOrigin()
{
	Text.setOrigin(GetCenter());
}
