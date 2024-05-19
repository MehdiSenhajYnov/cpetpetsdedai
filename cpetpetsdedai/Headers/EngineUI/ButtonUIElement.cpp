#include "ButtonUIElement.h"

ButtonUIElement::~ButtonUIElement() = default;


void ButtonUIElement::Update(float _deltaTime)
{
    ButtonAppearance::Update(_deltaTime);
    IClickable::Update(_deltaTime);
}

void ButtonUIElement::SetPosition(const sf::Vector2f& _position)
{
    ButtonAppearance::SetPosition(_position);
}

void ButtonUIElement::Init(sf::RenderWindow* _window)
{
    ButtonAppearance::Init(_window);
    SetBaseColor(backgroundColor);
    SetHoverColor(sf::Color(150,150,150));
    SetPressedColor(sf::Color(100,100,100));
    SetSize({200, 50});
    GetText()->SetText("Button");
}

sf::Vector2f ButtonUIElement::GetClickablePosition()
{
    return background.getPosition();
}

sf::Vector2f ButtonUIElement::GetClickableSize()
{
    return background.getSize();
}

void ButtonUIElement::ChangeColor(sf::Color _newColor, ClickableState _newState) 
{
    SetBackgroundColor(_newColor);
}
