#include "Inspector.h"

#include "SelectionSystem.h"
#include "../Engine/GameObject.h"

DefaultConstructor(Inspector, Panel)

void Inspector::Draw(sf::RenderWindow* _window)
{
    Panel::Draw(_window);
    for (auto& contentName : properties)
    {
        contentName.Draw(_window);
    }
    for (auto& element : properties)
    {
        element.Draw(_window);
    }
}

void Inspector::Init(sf::RenderWindow* _window, sf::Cursor* _cursor)
{
    Panel::Init(_window, _cursor);
    SelectionSystem::OnSelectionChanged.Subscribe(&Inspector::UpdateContentNames, this);

}

void Inspector::UpdateContentNames(GameObject* _object)
{
    properties.clear();
    currentMaxHeigth = 0.0f;
    for (auto& element : _object->GetType()->GetAllFields())
    {
        properties.push_back(InspectorProperty());
        properties.back().Init(window, cursor);
        properties.back().AddPropertyValue();

        properties.back().GetPropertyValues().back().GetPlaceholder()->SetText(element->name);
        SerializeBuffer buffer;
        element->Serialize(buffer, "");
        properties.back().GetPropertyValues().back().GetText()->SetText(buffer.GetAll());
        
        
        properties.back().GetPropertyName().SetText(element->name + " : ");
        if (properties.back().GetSize().y > currentMaxHeigth)
        {
            currentMaxHeigth = properties.back().GetSize().y;
        }
        //contentNames.back().SetPosition(GetAvaiblePosition());
        //HoldSpace(contentNames.back().GetSize());
    }

    UpdatePosition();
}



void Inspector::Update(float _deltaTime)
{
    Panel::Update(_deltaTime);
    for (auto& element : properties)
    {
        element.Update(_deltaTime);
    }
}

void Inspector::UpdatePosition()
{
    ResetSpaceHolded();
    for (auto& element : properties)
    {
        element.SetPosition(GetAvaiblePosition() + sf::Vector2f(leftPadding, 0));
        HoldSpace({ element.GetSize().x, currentMaxHeigth });
    }
}

void Inspector::SetPosition(const sf::Vector2f& _position)
{
    Panel::SetPosition(_position);
    UpdatePosition();
}

void Inspector::ResetSpaceHolded()
{
    Panel::ResetSpaceHolded();
    HoldSpace(titleOffset);
}
