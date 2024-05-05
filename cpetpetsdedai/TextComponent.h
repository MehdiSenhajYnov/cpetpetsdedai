#pragma once
#include <SFML/Graphics/Text.hpp>

#include "Headers/Components/DrawableComponent.h"

class TextComponent : public DrawableComponent {
public:
	TextComponent();

	TextComponent(const std::string& _typeName, Type* parentType);

	void                Init() override;
	void                Init(std::string _text);
	AddType(TextComponent, DrawableComponent::GetStaticType());
	
	void                SetString(std::string _buttonString);
	std::string         GetString() const;
	void                Start() override;
	const sf::Drawable* GetDrawable() override;
	void                setPosition(sf::Vector2f pos) override;
	sf::Vector2f        GetOriginalSize() override;
	sf::FloatRect       GetBounds() override;
	sf::Text            Text;

	void      SetColor(const sf::Color& _color);
	sf::Color GetColor() const;
	void      SetDrawScale(sf::Vector2f _drawScale) override;
	sf::Vector2f GetCenter() const ;

	void SetFontSize(int _fontSize);
	void ResetOrigin();
private:
	static sf::Font font;
	static bool fontLoaded;
	
};
