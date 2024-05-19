#include "InspectorProperty.h"

InspectorProperty::~InspectorProperty()
{
    for(auto _val : propertyValues)
    {
        Factory::GetInstance()->DestroyObject(_val);
    }
    propertyValues.clear();

    Factory::GetInstance()->DestroyObject(propertyName);
}

void InspectorProperty::Draw(sf::RenderWindow* _window)
{
    propertyName->Draw(window);
    for (auto& propertyValue : propertyValues)
    {
        if (propertyValue == nullptr)
        {
            continue;
        }
        propertyValue->Draw(window);
    }
}

void InspectorProperty::Update(float _deltaTime)
{
    for (auto& propertyValue : propertyValues)
    {
        propertyValue->Update(_deltaTime);
    }
}

void InspectorProperty::Init(sf::RenderWindow* _window)
{
    EngineUIElement::Init(_window);
    if (propertyName == nullptr)
    {
        Factory::GetInstance()->DestroyObject(propertyName);
    }
    propertyName = Factory::GetInstance()->CreateObject<TextUIElement>();

    propertyName->Init(_window);
    for (auto& propertyValue : propertyValues)
    {
        propertyValue->Init(_window);
    }

}

void InspectorProperty::SetPosition(const sf::Vector2f& _position)
{
    EngineUIElement::SetPosition(_position);

    propertyName->SetPosition(_position);
    for (int i = 0; i < propertyValues.size(); ++i)
    {
        // if (alignType == AlignType::Manual)
        // {
        //     propertyValues[i]->SetPosition(_position + absoluteFirstValueOffset * (float)i);
        // } 
        if (alignType == AlignType::AutoVertical)
        {
            if (i == 0)
            {
                propertyValues[i]->SetPosition(_position + sf::Vector2f(0,propertyName->GetSize().y + padding));
            }
            else
            {
                propertyValues[i]->SetPosition(propertyValues[i - 1]->GetPosition() + sf::Vector2f(0, propertyValues[i - 1]->GetSize().y + padding));
            }
        }
        else if (alignType == AlignType::AutoHorizontal)
        {
            if (i == 0)
            {
                propertyValues[i]->SetPosition(_position + sf::Vector2f(propertyName->GetSize().x + padding, 0));
            }
            else
            {
                propertyValues[i]->SetPosition(propertyValues[i - 1]->GetPosition() + sf::Vector2f( propertyValues[i - 1]->GetSize().x + padding, 0));
            }
        }
        
    }

}

void InspectorProperty::AddPropertyValue(TextInput* _propertyValue)
{
    propertyValues.push_back(_propertyValue);
    if (_propertyValue != nullptr && !_propertyValue->GetIsInitialized())
    {
        propertyValues.back()->Init(window);
    }
}

void InspectorProperty::AddPropertyValue()
{
    TextInput* toAdd = Factory::GetInstance()->CreateObject<TextInput>();
    AddPropertyValue(toAdd);
}

sf::Vector2f InspectorProperty::GetSize() const
{
    if (propertyValues.empty())
    {
        return propertyName->GetSize();
    }
    //return propertyValues.back()->GetSize();

    float sizeWidth = propertyName->GetSize().x;
    float sizeHeight = propertyName->GetSize().y;

    for (auto& propertyValue : propertyValues)
    {
        if (alignType == AutoVertical)
        {
            if (propertyValue->GetSize().x > sizeWidth)
            {
                sizeWidth = propertyValue->GetSize().x;
            }
            sizeHeight += propertyValue->GetSize().y + padding;
        } else if (alignType == AutoHorizontal)
        {
            sizeWidth += propertyValue->GetSize().x + padding;
            if (propertyValue->GetSize().y > sizeHeight)
            {
                sizeHeight = propertyValue->GetSize().y;
            }
        }
    
    }

    return {sizeWidth, sizeHeight};
}

