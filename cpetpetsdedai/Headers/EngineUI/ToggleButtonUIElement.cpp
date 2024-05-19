#include "ToggleButtonUIElement.h"

ToggleButtonUIElement::~ToggleButtonUIElement() = default;


void ToggleButtonUIElement::Update(float _deltaTime)
{
    ButtonAppearance::Update(_deltaTime);
    ISelectable::Update(_deltaTime);
}

void ToggleButtonUIElement::SetPosition(const sf::Vector2f& _position)
{
    ButtonAppearance::SetPosition(_position);
}

void ToggleButtonUIElement::Init(sf::RenderWindow* _window)
{
    ButtonAppearance::Init(_window);
    SetBaseColor(backgroundColor);
    SetHoverColor(sf::Color(150,150,150));
    SetPressedColor(sf::Color(100,100,100));
    SetSelectedColor(sf::Color(50,50,50));
    SetSize({200, 50});
    GetText()->SetText("Button");
}

sf::Vector2f ToggleButtonUIElement::GetSelectablePosition()
{
    return background.getPosition();
}

sf::Vector2f ToggleButtonUIElement::GetSelectableSize()
{
    return background.getSize();
}

void ToggleButtonUIElement::ChangeColor(sf::Color _newColor, SelectableState _newState) 
{
    SetBackgroundColor(_newColor);
}
