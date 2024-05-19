#include "HorizontalAlignment.h"

void HorizontalAlignment::UpdatePositionOfElement(EngineUIElement* _elementInstance, int _index)
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
        elementPosition = currentTopRight + sf::Vector2f(0,  spaceBetweenButtons);
    }
    else
    {
        elementPosition = GetPosition();
    }
    _elementInstance->SetPosition(elementPosition);
    
    currentTopRight = elementPosition + sf::Vector2f(_elementInstance->GetSize().x, 0);
    currentBottomLeft = elementPosition + sf::Vector2f(0,_elementInstance->GetSize().y - _elementInstance->GetOrigin().y);
    currentBottomRight = currentBottomLeft + sf::Vector2f(_elementInstance->GetSize().x,0);
}
