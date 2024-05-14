#include "Inspector.h"

#include "SelectionSystem.h"
#include "../Engine/GameObject.h"

DefaultConstructor(Inspector, Panel)

Inspector::~Inspector()
{
    for(auto property : properties)
    {
        Factory::GetInstance()->DestroyObject(property);
    }
    properties.clear();
}

void Inspector::Draw(sf::RenderWindow* _window)
{
    Panel::Draw(_window);
    for (auto& contentName : properties)
    {
        contentName->Draw(_window);
    }
    for (auto& element : properties)
    {
        element->Draw(_window);
    }
}

void Inspector::Init(sf::RenderWindow* _window)
{
    Panel::Init(_window);
    SelectionSystem::OnSelectionChanged.Subscribe(&Inspector::UpdateContentNames, this);

}

void Inspector::UpdateContentNames(GameObject* _object)
{
    std::cout << "INSPECTOR : new object selected" << std::endl;
    properties.clear();
    currentMaxHeigth = 0.0f;
    for (auto& element : _object->GetType()->GetAllFields())
    {
        properties.push_back(Factory::GetInstance()->CreateObject<InspectorProperty>());
        properties.back()->Init(window);
        properties.back()->AddPropertyValue();

        
        properties.back()->GetPropertyValues().back()->GetPlaceholder()->SetText(element->name);
        SerializeBuffer buffer;
        element->Serialize(buffer, "");
        properties.back()->GetPropertyValues().back()->GetText()->SetText(buffer.GetAll());

        
        properties.back()->GetPropertyName()->SetText(element->name + " : ");
        InspectorProperty* currentProperty = properties.back();
        std::string currentContent = buffer.GetAll();
        auto lambda = [this,&element, currentContent, currentProperty](std::string _textInput) {
            ValueSubmitted(_textInput, currentContent, element, currentProperty);
        };
        
        properties.back()->GetPropertyValues().back()->TextSubmit.Subscribe(lambda);


        if (properties.back()->GetSize().y > currentMaxHeigth)
        {
            currentMaxHeigth = properties.back()->GetSize().y;
        }
        
        //contentNames.back()->SetPosition(GetAvaiblePosition());
        //HoldSpace(contentNames.back()->GetSize());
    }

    UpdatePosition();
}



void Inspector::Update(float _deltaTime)
{
    Panel::Update(_deltaTime);
    for (auto& element : properties)
    {
        element->Update(_deltaTime);
    }
}

void Inspector::UpdatePosition()
{
    ResetSpaceHolded();
    for (auto& element : properties)
    {
        element->SetPosition(GetAvaiblePosition() + sf::Vector2f(leftPadding, 0));
        HoldSpace({ element->GetSize().x, currentMaxHeigth });
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

void Inspector::AddProperty()
{
    AddProperty(Factory::GetInstance()->CreateObject<InspectorProperty>());
}

void Inspector::AddProperty(InspectorProperty* _property)
{
    properties.push_back(_property);
    _property->Init(window);
    _property->AddPropertyValue();
    UpdatePosition();
}

void Inspector::RemoveProperty(InspectorProperty* _property)
{
    properties.RemoveElement(_property);
    Factory::GetInstance()->DestroyObject(_property);
    UpdatePosition();
}

void Inspector::ValueSubmitted(std::string _textInput,std::string baseText, BaseField* _field, InspectorProperty* curproperty)
{
    bool canDeserialize = _field->DeserializeNoName(_textInput, _textInput);
    if (!canDeserialize)
    {
        curproperty->GetPropertyValues().back()->GetText()->SetText(baseText);
        std::cout << "INSPECTOR : Could not deserialize" << std::endl;
    } else
    {
        std::cout << "INSPECTOR : Deserialized !" << std::endl;
    }
    
    
}
