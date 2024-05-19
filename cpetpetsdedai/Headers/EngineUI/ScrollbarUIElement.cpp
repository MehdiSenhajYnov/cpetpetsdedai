#include "ScrollbarUIElement.h"

#include "../Input/Input.h"

void ScrollbarUiElement::Draw(sf::RenderWindow* _window)
{
    if (!isActive) return;
    window->draw(scrollbar);
}

void ScrollbarUiElement::Update(float _deltaTime)
{
    if (!isActive)
    {
        if (isDragging)
        {
            isDragging = false;
            SetColor(baseColor);
        }
        return;
    }
    sf::Vector2f mousePos = Input::GetMousePosition();
    
    if (Input::GetKeyDown(KeyCode::LeftMouse) )
    {
        // bool isInBoundX = mousePos.x > GetPosition().x && mousePos.x < GetPosition().x + GetSize().x;
        // bool isInBoundY = mousePos.y > GetPosition().y && mousePos.y < GetPosition().y + GetSize().y;
        if (Utilities::IsInBounds(mousePos, scrollbar.getPosition(), scrollbar.getSize(), InBoundsInputType::Center ))
        {
            isDragging = true;
            yOffset = mousePos.y - scrollbar.getPosition().y;
            SetColor(hoverColor);
        }
    }
    if (Input::GetKeyUp(KeyCode::LeftMouse))
    {
        isDragging = false;
        SetColor(baseColor);
    }
    if (isDragging)
    {
        scrollbar.setPosition(GetPosition().x, mousePos.y - yOffset);
        if (scrollbar.getPosition().y < minY)
        {
            scrollbar.setPosition(GetPosition().x, minY);
        }
        if (maxY > minY && scrollbar.getPosition().y > maxY)
        {
            scrollbar.setPosition(GetPosition().x, maxY);
        }
        OnPositionChanged.InvokeEvent(scrollbar.getPosition(), GetPercentage());
    }
}

void ScrollbarUiElement::SetColor(const sf::Color& _color)
{
    scrollbar.setFillColor(_color);
    currentColor = _color;
}

void ScrollbarUiElement::Init(sf::RenderWindow* _window)
{
    EngineUIElement::Init(_window);
    scrollbar = sf::RectangleShape();
    SetColor(baseColor);
    SetSize({ 10, 100 });
}

void ScrollbarUiElement::SetSize(const sf::Vector2f& _size)
{
    EngineUIElement::SetSize(_size);
    scrollbar.setSize(_size);
    scrollbar.setOrigin(_size / 2.0f);
    SetMinMaxY(userMinY, userMaxY);
}

void ScrollbarUiElement::SetPosition(const sf::Vector2f& _position)
{
    EngineUIElement::SetPosition(_position);
    scrollbar.setPosition(_position);
}

void ScrollbarUiElement::ResetY()
{
    scrollbar.setPosition(GetPosition().x, minY);
}
