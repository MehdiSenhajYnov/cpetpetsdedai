#include "TextInput.h"
#include "../Input/Input.h"

DefaultConstructor(TextInput, EngineUIElement)

void TextInput::Draw(sf::RenderWindow* window)
{
    window->draw(background);
    if (text.GetText()->getString().isEmpty())
    {
        placeholder.Draw(window);
    }
    else
    {
        text.Draw(window);
    }
    if (isCarretVisible)
    {
        window->draw(carret);
    }
}

void TextInput::Update(float _deltaTime)
{
    ISelectable::Update(_deltaTime);
    if (GetSelectableState() == SelectableState::Selected)
    {
        
        if (Input::GetKeyDown(KeyCode::Backspace))
        {
            std::string oldText = text.GetText()->getString();
            if (!oldText.empty())
            {
                oldText.pop_back();
                text.SetText(oldText);
            }
        }
        if (Input::GetKeyDown(KeyCode::Enter))
        {
            TextSubmit.InvokeEvent(text.GetText()->getString());
            Deselect();
        }

        carretBlinkTimer += _deltaTime;
        if (carretBlinkTimer >= carretBlinkTime)
        {
            carretBlinkTimer = 0.0f;
            isCarretVisible = !isCarretVisible;
        }
    }
    else
    {
        isCarretVisible = false;
        carretBlinkTimer = 0.0f;
    }
    
}

void TextInput::Init(sf::RenderWindow* _window, sf::Cursor* _cursor)
{
    EngineUIElement::Init(_window, _cursor);
    text.Init(_window, _cursor);
    placeholder.Init(_window, _cursor);
    text.SetVerticalOriginToCenter();
    placeholder.SetVerticalOriginToCenter();
    
    
    text.OnTextChange.Subscribe(&TextInput::OnTextChange, this);
    placeholder.SetText("Type here...");

    background.setSize({ 200, 50 });
    background.setFillColor(sf::Color::White);
    background.setOutlineColor(sf::Color::Black);
    background.setOutlineThickness(1);

    carret.setSize({ 2, 40 });
    carret.setFillColor(sf::Color::Black);
    
    placeholder.SetFillColor(sf::Color(120,120, 120));
    SetPosition(GetPosition());

    
    Input::textEnteredEvent.Subscribe(&TextInput::OnUserText, this);

    SetBaseColor(sf::Color::Black);
    SetSelectedColor(sf::Color::Cyan);
    SetDisabledColor(sf::Color::Transparent);

    OnMouseEnter.Subscribe(&TextInput::ChangeCursorToTextInput, this);
    OnMouseExit.Subscribe(&TextInput::ChangeCursorToDefault, this);


    OnSelect.Subscribe(&TextInput::CarretOnSelect, this);
}

void TextInput::SetPosition(const sf::Vector2f& _position)
{
    EngineUIElement::SetPosition(_position);
    background.setPosition(_position);
    float textYCenter = _position.y + (background.getSize().y/ 2) - text.GetSize().y / 2;
    text.SetPosition({ _position.x + textLeftPadding, textYCenter });
    placeholder.SetPosition({ _position.x + textLeftPadding, textYCenter });
}

void TextInput::OnUserText(char _char)
{
    if (GetSelectableState() != SelectableState::Selected) return;
    if (!ProcessCharInput(_char)) return;
    std::string oldText = text.GetText()->getString();
    text.SetText(text.GetText()->getString() + _char);
    
    if (text.GetSize().x > background.getSize().x)
    {
        text.SetText(oldText);
    }
}

void TextInput::OnTextChange(const std::string& _text)
{
    UpdateCarretPosition();
}

bool TextInput::ProcessCharInput(char _char)
{
    if (inputType == Normal )
    {
        return true;
    }

    if (inputType == Integers)
    {
        if (_char == '-' || (_char >= '0' && _char <= '9'))
        {
            return true;
        }
    }
    if (inputType == Numbers)
    {
        if (_char >= '0' && _char <= '9')
        {
            return true;
        }
        if (_char == '.' && text.GetText()->getString().find('.') == std::string::npos)
        {
            return true;
        }
    }
    if (inputType == Alpha)
    {
        if ((_char >= 'a' && _char <= 'z') || (_char >= 'A' && _char <= 'Z'))
        {
            return true;
        }
    }
    if (inputType == Alphanumeric)
    {
        if ((_char >= 'a' && _char <= 'z') || (_char >= 'A' && _char <= 'Z') || (_char >= '0' && _char <= '9'))
        {
            return true;
        }
    }
    if (inputType == One)
    {
        if (text.GetText()->getString().isEmpty())
        {
            return true;
        }
    }
    if (inputType == OneAlpha)
    {
        if (text.GetText()->getString().isEmpty() && ((_char >= 'a' && _char <= 'z') || (_char >= 'A' && _char <= 'Z')))
        {
            return true;
        }
    }
    if (inputType == OneNumber)
    {
        if (text.GetText()->getString().isEmpty() && (_char >= '0' && _char <= '9'))
        {
            return true;
        }
    }
    return false;
    
}

void TextInput::UpdateCarretPosition()
{
    carret.setPosition(GetPosition().x + text.GetSize().x + carretLeftPadding, GetPosition().y + (background.getSize().y - carret.getSize().y) / 2);
}

void TextInput::ChangeCursorToTextInput(ISelectable* _selectable)
{
    ChangeCursor(sf::Cursor::Type::Text);
}

void TextInput::ChangeCursorToDefault(ISelectable* _selectable)
{
    ChangeCursor(sf::Cursor::Type::Arrow);
}

void TextInput::ChangeColor(sf::Color _newColor)
{
    background.setOutlineColor(_newColor);
}

sf::Vector2f TextInput::GetSelectablePosition()
{
    return GetPosition();
}

sf::Vector2f TextInput::GetSelectableSize()
{
    return background.getSize();
}

void TextInput::CarretOnSelect(ISelectable* _selectable)
{
    isCarretVisible = true;
    UpdateCarretPosition();
}
