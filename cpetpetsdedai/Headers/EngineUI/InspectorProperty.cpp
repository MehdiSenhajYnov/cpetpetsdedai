#include "InspectorProperty.h"

void InspectorProperty::Draw(sf::RenderWindow* window)
{
    propertyName.Draw(window);
    for (auto& propertyValue : propertyValues)
    {
        propertyValue.Draw(window);
    }
}

void InspectorProperty::Update(float _deltaTime)
{
    for (auto& propertyValue : propertyValues)
    {
        propertyValue.Update(_deltaTime);
    }
}

void InspectorProperty::Init(sf::RenderWindow* _window, sf::Cursor* _cursor)
{
    EngineUIElement::Init(_window, _cursor);

    propertyName.Init(_window, _cursor);
    for (auto& propertyValue : propertyValues)
    {
        propertyValue.Init(_window, _cursor);
    }

}

void InspectorProperty::SetPosition(const sf::Vector2f& _position)
{
    EngineUIElement::SetPosition(_position);

    propertyName.SetPosition(_position);
    for (int i = 0; i < propertyValues.size(); ++i)
    {
        if (alignType == AutoVertical)
        {
            if (i == 0)
            {
                propertyValues[i].SetPosition(_position + sf::Vector2f(0,propertyName.GetSize().x + padding));
            }
            else
            {
                propertyValues[i].SetPosition(propertyValues[i - 1].GetPosition() + sf::Vector2f(0, propertyValues[i - 1].GetSize().x + padding));
            }
        }
        else if (alignType == Horizontal)
        {
            if (i == 0)
            {
                propertyValues[i].SetPosition(_position + sf::Vector2f(propertyName.GetSize().x + padding, 0));
            }
            else
            {
                propertyValues[i].SetPosition(propertyValues[i - 1].GetPosition() + sf::Vector2f( propertyValues[i - 1].GetSize().x + padding, 0));
            }
        }
        else if (alignType == Manual)
        {
            propertyValues[i].SetPosition(_position + absoluteFirstValueOffset * (float)i);
        }
    }

}

void InspectorProperty::AddPropertyValue(TextInput _propertyValue)
{
    propertyValues.push_back(_propertyValue);
    propertyValues.back().Init(window, cursor);
}

void InspectorProperty::AddPropertyValue()
{
    AddPropertyValue(TextInput());
}

sf::Vector2f InspectorProperty::GetSize() const
{
    if (propertyValues.empty())
    {
        return propertyName.GetSize();
    } 
    else
    {
                // Bottom right corner of the last property value - top left corner of the property name 
        return (propertyValues.back().GetPosition() + propertyValues.back().GetSize()) - propertyName.GetPosition();
    }
}

