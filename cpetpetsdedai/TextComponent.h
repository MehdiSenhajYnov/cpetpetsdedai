#pragma once
#include <SFML/Graphics/Text.hpp>

#include "Headers/Components/DrawableComponent.h"

class TextComponent : public DrawableComponent {
public:
	void                Init() override;
	void                Init(std::string _text);

	
	void                SetString(std::string _buttonString);
	void                Start() override;
	const sf::Drawable* GetDrawable() override;
	void                setPosition(sf::Vector2f pos) override;
	sf::Vector2f        GetSize() override;
	sf::FloatRect       GetBounds() override;
	sf::Text            Text;

	void      SetColor(const sf::Color& _color);
	sf::Color GetColor() const;
	void      SetDrawScale(sf::Vector2f _drawScale) override;

private:
	static sf::Font font;
	static bool fontLoaded;
	
};
