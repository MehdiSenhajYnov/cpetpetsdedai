#pragma once
#include <SFML/Graphics/RectangleShape.hpp>

#include "../../Sources/EngineUIElement.h"

class TextUIElement;

class ButtonAppearance : public EngineUIElement
{
public:
    ADD_TYPE(ButtonAppearance, EngineUIElement, REG_TYPE);
    ButtonAppearance();
    ButtonAppearance(const std::string& _typeName, Type* parentType);
    ~ButtonAppearance() override;

    void Init(sf::RenderWindow* _window) override;
    
    sf::RectangleShape& GetBackground() { return background; }
    TextUIElement* GetText() const { return text; }
    
    void SetBackgroundColor(sf::Color _color);
    sf::Color GetBackgroundColor() const;

    void SetOutlineColor(sf::Color _color);
    sf::Color GetOutlineColor() const;

    void SetTextColor(sf::Color _color);
    sf::Color GetTextColor() const;


    void Draw(sf::RenderWindow* _window) override;
    void Update(float _deltaTime) override;
    void SetTextToCenter();

    void SetPosition(const sf::Vector2f& _position) override;

    void SetSize(const sf::Vector2f& _size) override;
    sf::Vector2f GetSize() const override;
    
    sf::Vector2f GetOrigin() const override;

protected:
    void TextChanged(const std::string& _newText);

    sf::RectangleShape background;
    TextUIElement* text = nullptr;
    
    sf::Color backgroundColor = sf::Color::White;
    sf::Color outlineColor = sf::Color::Black;
    sf::Color textColor = sf::Color::Black;
};
