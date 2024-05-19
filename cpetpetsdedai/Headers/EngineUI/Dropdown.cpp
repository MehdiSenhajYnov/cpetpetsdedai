#include "Dropdown.h"

#include "ButtonUIElement.h"
#include "VerticalAlignment.h"
#include "../GameSystem/TextureManager.h"


Dropdown::~Dropdown()
{
    if (verticalAlignment != nullptr)
    {
        Factory::GetInstance()->DestroyObject(verticalAlignment);
    }
    if (mainButton != nullptr)
    {
        Factory::GetInstance()->DestroyObject(mainButton);
    }
    for (auto& element : elements)
    {
        if (element != nullptr)
        {
            Factory::GetInstance()->DestroyObject(element);
        }
    }
    elements.clear();
}

void Dropdown::Draw(sf::RenderWindow* _window)
{
    if (mainButton == nullptr)
    {
        return;
    }
    if (isExpanded)
    {
        if (verticalAlignment != nullptr)
        {
            verticalAlignment->Draw(_window);
        }
    }
    else
    {
        mainButton->Draw(_window);
    }
    window->draw(openIcon);
}

void Dropdown::Update(float _deltaTime)
{
    verticalAlignment->Update(_deltaTime);
}

void Dropdown::SetPosition(const sf::Vector2f& _position)
{
    EngineUIElement::SetPosition(_position);
    if (verticalAlignment != nullptr)
    {
        verticalAlignment->SetPosition(_position);
    }
    UpdateIconPosition();
}

void Dropdown::SwitchOpenClose()
{
    if (isExpanded)
    {
        Close();
    }
    else
    {
        Open();
    }
}

void Dropdown::Open()
{
    isExpanded = true;
    openIcon.setTexture(*TextureManager::Instance()->GetTexture("OpenContextUp"));
}

void Dropdown::Close()
{
    isExpanded = false;
    openIcon.setTexture(*TextureManager::Instance()->GetTexture("OpenContextDown"));
}

void Dropdown::UpdateIconPosition()
{
    if (mainButton == nullptr)
    {
        return;
    }
    sf::Vector2f newPos = GetPosition() + sf::Vector2f(GetSize().x - openIcon.getGlobalBounds().width, mainButton->GetSize().y/2);
    openIcon.setPosition(newPos);
}

void Dropdown::SetMainText(const std::string& _text)
{
    if (mainButton != nullptr)
    {
        mainButton->GetText()->SetText(_text);
    }
}

sf::Vector2f Dropdown::GetSize() const
{
    if (isExpanded)
    {
        return verticalAlignment->GetSize();
    }
    return mainButton->GetSize();
}

void Dropdown::Init(sf::RenderWindow* _window)
{
    EngineUIElement::Init(_window);
    verticalAlignment = Create<VerticalAlignment>();
    verticalAlignment->SetSpaceBetweenButtons(5);
    verticalAlignment->Init(_window);
    verticalAlignment->SetPosition(GetPosition());
    
    mainButton = verticalAlignment->AddToContextMenu<ButtonUIElement>();
    mainButton->SetSize(GetSize());

    openIcon.setTexture(*TextureManager::Instance()->GetTexture("OpenContextDown"));
    openIcon.setScale(0.3f, 0.3f);
    openIcon.setColor(sf::Color::Black);
    openIcon.setOrigin(openIcon.getGlobalBounds().width/2, openIcon.getGlobalBounds().height/2);
    UpdateIconPosition();

    mainButton->OnClick.Subscribe([this](IClickable* _button) {
        SwitchOpenClose();
    });
}



ButtonUIElement* Dropdown::AddElement(const std::string& _elementName, std::function<void(IClickable*)> _function)
{
    ButtonUIElement* addedBtn = verticalAlignment->AddToContextMenu<ButtonUIElement>();
    addedBtn->GetText()->SetText(_elementName);
    addedBtn->SetSize(GetSize());
    addedBtn->OnClick.Subscribe(_function);
    
    elements.push_back(addedBtn);
    return addedBtn;
}


void Dropdown::SetSize(const sf::Vector2f& _size)
{
    EngineUIElement::SetSize(_size);
    if (mainButton != nullptr)
    {
        mainButton->SetSize(_size);
    }
    for (auto& element : elements)
    {
        element->SetSize(_size);
    }
    UpdateIconPosition();

}

