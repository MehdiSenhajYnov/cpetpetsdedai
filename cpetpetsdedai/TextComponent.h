#pragma once
#include <SFML/Graphics/Text.hpp>

#include "Headers/Components/DrawableComponent.h"

class TextComponent : public DrawableComponent {
public:
	TextComponent();

	TextComponent(const std::string& _typeName, Type* parentType);
	TextComponent(const uint64_t& _id, const std::string& _name, Type* parentType);
	TextComponent(uint64_t _id);

	void                Init() override;
	void                Init(std::string _text);
	AddType(TextComponent, DrawableComponent);
	
	void                SetString(std::string _newTextString);
	std::string         GetString() const;
	void                Start() override;
	const sf::Drawable* GetDrawable() override;
	void                setPosition(sf::Vector2f pos) override;
	sf::Vector2f        GetOriginalSize() override;
	sf::FloatRect       GetBounds() override;
	sf::Text            Text;

	void      SetColor(const sf::Color& _color) override;
	sf::Color GetColor() const override;
	void      SetDrawScale(sf::Vector2f _drawScale) override;
	sf::Vector2f GetCenter() const ;

	void SetFontSize(int _fontSize);
	void ResetOrigin();
private:
	static sf::Font font;
	static bool fontLoaded;
	std::string currentText;
};
