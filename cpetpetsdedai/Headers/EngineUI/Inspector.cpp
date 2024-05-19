#include "Inspector.h"

#include "SelectionSystem.h"
#include "VerticalAlignment.h"
#include "Dropdown.h"
#include "../Engine/GameObject.h"


Inspector::Inspector() : Inspector("Inspector", Panel::GetStaticType()) { }
Inspector::Inspector(const std::string& _typeName, Type* parentType) : Panel(_typeName, parentType) { }

Inspector::~Inspector()
{
    for(auto property : properties)
    {
        Factory::GetInstance()->DestroyObject(property);
    }
    properties.clear();
    propertiesFields.clear();
    if (verticalList != nullptr)
    {
        Factory::GetInstance()->DestroyObject(verticalList);
    }
    if (dropdown != nullptr)
    {
        Factory::GetInstance()->DestroyObject(dropdown);
    }
    
}

void Inspector::Draw(sf::RenderWindow* _window)
{
    Panel::Draw(_window);
    for (auto& contentName : properties)
    {
        contentName->Draw(_window);
    }

    verticalList->Draw(_window);
    scrollbar.Draw(_window);
}

void Inspector::Init(sf::RenderWindow* _window)
{
    Panel::Init(_window);
    currentWindowSize = window->getSize();
    SelectionSystem::OnSelectionChanged.Subscribe(&Inspector::UpdateSelectedObject, this);
    verticalList = Factory::GetInstance()->CreateObject<VerticalAlignment>();
    verticalList->Init(window);

    scrollbar.Init(window);
    scrollbar.SetPosition(sf::Vector2f((float)window->getSize().x - scrollbar.GetSize().x * 2, 0));
    scrollbar.SetColor(sf::Color(100, 100, 100));
    scrollbar.ResetY();
}

void Inspector::UpdateSelectedObject(GameObject* _object, std::string _selectionSystemName)
{
    if (_selectionSystemName != SELECTION_SYSTEM_NAME) return;
    
    properties.clear();
    propertiesFields.clear();
    currentMaxWidth = 0.0f;
    currentMaxHeigth = 0.0f;
    Factory::GetInstance()->DestroyObject(verticalList);

    if (_object == nullptr)
    {
        return;
    }
    
    verticalList = Factory::GetInstance()->CreateObject<VerticalAlignment>();
    verticalList->Init(window);

    InitPropertiesOnUpdate(_object);
    InitDropdownOnUpdate();

    if (currentMaxWidth > GetPanelWidth())
    {
        SetPanelWidth(currentMaxWidth + 10);
    }

    InitScrollbarOnUpdate();

}

void Inspector::InitPropertiesOnUpdate(GameObject* _object)
{

    properties.push_back(Factory::GetInstance()->CreateObject<InspectorProperty>());
    properties.back()->Init(window);
    properties.back()->GetPropertyName()->SetText("Gameobject : \n ");
    verticalList->AddToContextMenu(properties.back());


    for (auto& _field : _object->GetType()->GetAllFields())
    {
        if (_field->name == "components")
        {
            InitComponentsOnUpdate(_object, _field);
            continue;
        }
        AddProperty(_field);

        
        //contentNames.back()->SetPosition(GetAvaiblePosition());
        //HoldSpace(contentNames.back()->GetSize());
    }
}

void Inspector::InitComponentsOnUpdate(GameObject* _object, BaseField* _baseElement)
{
    Field<TList<Component*>>* componentsField = dynamic_cast<Field<TList<Component*>>*>(_baseElement);
    if (!componentsField)
    {
        std::cout << "INSPECTOR : Could not cast to Field<TList<Component*>>" << std::endl;
        return;
    }
    TList<Component*> components = componentsField->GetValue();
    for (auto& component : components)
    {
        properties.push_back(Factory::GetInstance()->CreateObject<InspectorProperty>());
        properties.back()->Init(window);
        properties.back()->GetPropertyName()->SetText(component->GetType()->GetName() + " : \n ");
        verticalList->AddToContextMenu(properties.back());
        
        for (auto& _field : component->GetType()->GetAllFields())
        {
            AddProperty(_field);
        }
    }
    
}

void Inspector::InitDropdownOnUpdate()
{
    if (dropdown != nullptr)
    {
        Factory::GetInstance()->DestroyObject(dropdown);
    }

    dropdown = verticalList->AddToContextMenu<Dropdown>();
    dropdown->SetMainText("Add Component");
    dropdown->SetSize(sf::Vector2f(300, 50));
    
    auto allComponentsType = Type::GetAllChildrenRecursive(Component::GetStaticType());
    for (auto componentsType : allComponentsType)
    {
        if (!Factory::GetInstance()->CanBeCreated(componentsType->GetName())) continue;
        dropdown->AddElement(componentsType->GetName(), [this,componentsType](IClickable* _button) {
            std::cout << "Button clicked : " << componentsType->GetName() << std::endl;
            
            if (SelectionSystem::GetSelectedObject(SELECTION_SYSTEM_NAME) != nullptr)
            {
                SelectionSystem::GetSelectedObject(SELECTION_SYSTEM_NAME)->AddComponentByName(componentsType->GetName());

                haveToRefreshInspector = true;
            }
            else
            {
                std::cout << "INSPECTOR : No object selected" << std::endl;
            }
        });
    }
}

void Inspector::InitScrollbarOnUpdate()
{
    // pourcentage voulu appliqué sur la taille qu'on veut
    float ySizeScrollbar = (float)window->getSize().y / verticalList->GetSize().y * ((float)window->getSize().y * 0.8f);
    float yMinScrollbar = (float)window->getSize().y * 0.1f;
    float yMaxScrollbar = (float)window->getSize().y * 0.9f;
    
    scrollbar.SetSize({ 10, (float)window->getSize().y / 2 });

    scrollbar.SetMinMaxY(yMinScrollbar, yMaxScrollbar);
    scrollbar.ResetY();
}

void Inspector::AddProperty(BaseField* _field)
{
    properties.push_back(Factory::GetInstance()->CreateObject<InspectorProperty>());
    properties.back()->Init(window);
    properties.back()->GetPropertyName()->SetText(_field->name + " : ");

    propertiesFields[properties.back()] = _field;
        
    properties.back()->AddPropertyValue();
    properties.back()->GetPropertyValues().back()->GetPlaceholder()->SetText(_field->name);
    SerializeBuffer buffer;
    _field->Serialize(buffer, "");
    properties.back()->GetPropertyValues().back()->SetText(buffer.mainBuffer);
        
    InspectorProperty* currentProperty = properties.back();
    std::string currentContent = buffer.GetAll();
    auto lambda = [this,_field, currentContent, currentProperty](std::string _textInput) {
        ValueSubmitted(_textInput, currentContent, _field, currentProperty);
    };
        
    properties.back()->GetPropertyValues().back()->TextSubmit.Subscribe(lambda);

    if (properties.back()->GetSize().x > currentMaxWidth)
    {
        currentMaxWidth = properties.back()->GetSize().x;
    }
        
    if (properties.back()->GetSize().y > currentMaxHeigth)
    {
        currentMaxHeigth = properties.back()->GetSize().y;
    }
        
    verticalList->AddToContextMenu(properties.back());
}

void Inspector::Update(const float _deltaTime)
{
    if (!isInitialized) return;
    Panel::Update(_deltaTime);

    if (currentWindowSize != window->getSize())
    {
        currentWindowSize = window->getSize();
        OnWindowResize(currentWindowSize);
    }
    
    scrollbar.Update(_deltaTime);

    if (haveToRefreshInspector)
    {
        haveToRefreshInspector = false;
        UpdateSelectedObject(SelectionSystem::GetSelectedObject(SELECTION_SYSTEM_NAME), SELECTION_SYSTEM_NAME);
    }
    if (verticalList != nullptr)
    {
        verticalList->Update(_deltaTime);
    }

    // if ((float)window->getSize().y < verticalList->GetSize().y)
    // {
    //     scrollbar.SetActive(true);
    // }
    // else
    // {
    //     scrollbar.SetActive(false);
    // }

    for (auto& [_inspectorProperty, _field] : propertiesFields)
    {
        if (_inspectorProperty->GetPropertyValues().back()->GetSelectableState() == SelectableState::Selected)
        {
            continue;
        }
        SerializeBuffer buffer;
        _field->Serialize(buffer, "");
        _inspectorProperty->GetPropertyValues().back()->SetText(buffer.mainBuffer);
    }
    
    UpdatePosition();
}

void Inspector::UpdatePosition()
{
    ResetSpaceHolded();
    
    // setting vertical list position using scrollbar percentage
    sf::Vector2f newPos = GetAvaiblePosition() + sf::Vector2f(leftPadding, 0) +
        sf::Vector2f(0, -scrollbar.GetPercentage() * (verticalList->GetSize().y - ((float)window->getSize().y - 200)));
    verticalList->SetPosition(newPos);
    
}

void Inspector::SetPosition(const sf::Vector2f& _position)
{
    Panel::SetPosition(_position);
    ResetSpaceHolded();

    UpdatePosition();
    // sf::Vector2f newPos = GetPosition() + sf::Vector2f(leftPadding, 0) + sf::Vector2f(0, -scrollbar.GetPercentage() * (verticalList->GetSize().y - window->getSize().y));
    // verticalList->SetPosition(newPos);
    
    //verticalList->SetPosition(GetAvaiblePosition() + sf::Vector2f(leftPadding, 0));
}

void Inspector::ResetSpaceHolded()
{
    Panel::ResetSpaceHolded();
    HoldSpace(titleOffset);
}

void Inspector::ValueSubmitted(std::string _textInput,std::string baseText, BaseField* _field, InspectorProperty* curproperty)
{
    bool canDeserialize = _field->DeserializeNoName(_textInput, _textInput);
    if (!canDeserialize)
    {
        curproperty->GetPropertyValues().back()->SetText(baseText);
        std::cout << "INSPECTOR : Could not deserialize" << std::endl;
    } else
    {
        std::cout << "INSPECTOR : Deserialized !" << std::endl;
    }
}

void Inspector::OnWindowResize(sf::Vector2u _newSize)
{
    UpdatePosition();
    InitScrollbarOnUpdate();
    scrollbar.SetPosition(sf::Vector2f((float)window->getSize().x - scrollbar.GetSize().x * 2, 0));

}
