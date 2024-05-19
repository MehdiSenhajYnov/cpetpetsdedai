#include "ButtonAppearance.h"
#include "../../TextUIElement.h"


ButtonAppearance::ButtonAppearance(): ButtonAppearance("ButtonAppearance", EngineUIElement::GetStaticType())
{
    
}

ButtonAppearance::ButtonAppearance(const std::string& _typeName, Type* parentType): EngineUIElement(_typeName, parentType)
{

}

void ButtonAppearance::TextChanged(const std::string& _newText)
{
    text->SetOriginToCenter();
    SetTextToCenter();
}

void ButtonAppearance::Init(sf::RenderWindow* _window)
{
    EngineUIElement::Init(_window);
    text = Factory::GetInstance()->CreateObject<TextUIElement>();
    text->Init(window);
    text->SetOriginToCenter();
    text->OnTextChange.Subscribe(&ButtonAppearance::TextChanged, this);

    background.setFillColor(backgroundColor);
    background.setOutlineColor(outlineColor);
    background.setOutlineThickness(1.0f);
    
}

void ButtonAppearance::SetPosition(const sf::Vector2f& _position)
{
    EngineUIElement::SetPosition(_position);
    background.setPosition(_position);
    SetTextToCenter();
}

void ButtonAppearance::SetSize(const sf::Vector2f& _size)
{
    EngineUIElement::SetSize(_size);
    background.setSize(_size);
    SetTextToCenter();
}

sf::Vector2f ButtonAppearance::GetSize() const
{
    return background.getSize();
}

sf::Vector2f ButtonAppearance::GetOrigin() const
{
    return background.getOrigin();
}



ButtonAppearance::~ButtonAppearance()
{
    if (text != nullptr)
    {
        Factory::GetInstance()->DestroyObject(text);
    }
}

void ButtonAppearance::SetBackgroundColor(sf::Color _color)
{
    backgroundColor = _color;
    background.setFillColor(backgroundColor);
}

sf::Color ButtonAppearance::GetBackgroundColor() const
{
    return backgroundColor;
}

void ButtonAppearance::SetOutlineColor(sf::Color _color)
{
    outlineColor = _color;
    background.setOutlineColor(outlineColor);
}

sf::Color ButtonAppearance::GetOutlineColor() const
{
    return outlineColor;
}

void ButtonAppearance::SetTextColor(sf::Color _color)
{
    if (text == nullptr) { return; }
    textColor = _color;
    text->SetFillColor(textColor);
}

sf::Color ButtonAppearance::GetTextColor() const
{
    return textColor;
}

void ButtonAppearance::Draw(sf::RenderWindow* _window)
{
    if (window == nullptr)
    {
        return;
    }
    window->draw(background);
    if (text != nullptr)
    {
        text->Draw(window);
    }
}

void ButtonAppearance::Update(float _deltaTime)
{
    
}

void ButtonAppearance::SetTextToCenter()
{
    if (text == nullptr)
    {
        return;
    }
    text->SetPosition(sf::Vector2f(background.getPosition().x + background.getSize().x / 2, background.getPosition().y + background.getSize().y / 2));
}
