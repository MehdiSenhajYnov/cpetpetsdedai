#include "VerticalAlignment.h"

void VerticalAlignment::UpdatePositionOfElement(EngineUIElement* _elementInstance, int _index)
{
    if (_index >= elements.size())
    {
        return;
    }
    if (_elementInstance == nullptr)
    {
        return;
    }
    sf::Vector2f elementPosition;
    if (_index > 0)
    {
        elementPosition = currentBottomLeft + sf::Vector2f(0,  spaceBetweenButtons);
    }
    else
    {
        elementPosition = GetPosition();
        currentTopRight = GetPosition() + sf::Vector2f(_elementInstance->GetSize().x, 0);
    }
    _elementInstance->SetPosition(elementPosition);
    currentBottomLeft = elementPosition + sf::Vector2f(0,_elementInstance->GetSize().y - _elementInstance->GetOrigin().y);
    currentBottomRight = currentBottomLeft + sf::Vector2f(_elementInstance->GetSize().x,0);
}