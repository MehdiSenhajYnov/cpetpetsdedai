#include "TextInput.h"
#include "../Input/Input.h"
#include "../Utilities/MyMath.h"

DefaultConstructor(TextInput, EngineUIElement)

void TextInput::Draw(sf::RenderWindow* _window)
{
    if (window == nullptr) return;
    if (isBackgroundVisible)
    {
        window->draw(background);
    }
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
        UpdateCarretPosition();
        if (Input::GetKeyDown(KeyCode::LeftArrow))
        {
            DecreaseCarretIndex();
        }
        if (Input::GetKeyDown(KeyCode::RightArrow))
        {
            IncreaseCarretIndex();
        }
        if (Input::GetKeyDown(KeyCode::Backspace))
        {
            std::string oldText = text.GetText()->getString();
            if (!oldText.empty() && carretIndex > 0)
            {
                //oldText.pop_back();
                oldText.erase(carretIndex - 1, 1);
                
                text.SetText(oldText);
                DecreaseCarretIndex();
                if (sizeType == Adaptive)
                {
                    AdaptSize();
                }
            }
        }
        if (Input::GetKeyDown(KeyCode::Enter))
        {
            if (Input::GetKey(KeyCode::LShift) || Input::GetKey(KeyCode::RShift))
            {
                //text.SetText(text.GetText()->getString() + '\n');                
                OnUserText('\n');
            } else
            {
                TextSubmit.InvokeEvent(text.GetText()->getString());
                Deselect();
            }
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

void TextInput::Init(sf::RenderWindow* _window)
{
    EngineUIElement::Init(_window);

    background = sf::RectangleShape();
    carret = sf::RectangleShape();
    text = TextUIElement();
    placeholder = TextUIElement();
    
    text.Init(_window);
    placeholder.Init(_window);
    text.SetVerticalOriginToCenter();
    placeholder.SetVerticalOriginToCenter();
    
    
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

    // SetBaseColor(colorWithAlpha(sf::Color::Black, 255));
    // SetSelectedColor(colorWithAlpha(sf::Color::Cyan));
    // SetDisabledColor(sf::Color::Transparent);

    OnMouseEnter.Subscribe(&TextInput::ChangeCursorToTextInput, this);
    OnMouseExit.Subscribe(&TextInput::ChangeCursorToDefault, this);


    OnSelect.Subscribe(&TextInput::CarretOnSelect, this);
}

sf::Color TextInput::colorWithAlpha(sf::Color _tempColor, int _alpha)
{
    return sf::Color(_tempColor.r, _tempColor.g, _tempColor.b, 255);
}
    

void TextInput::SetPosition(const sf::Vector2f& _position)
{
    EngineUIElement::SetPosition(_position);
    background.setPosition(_position);
    float textYCenter = _position.y + (background.getSize().y/ 2) - text.GetSize().y / 2;
    text.SetPosition({ _position.x + textPadding.x, textYCenter });
    placeholder.SetPosition({ _position.x + textPadding.x, textYCenter });
}

void TextInput::AdaptSize()
{
    float xSize = text.GetSize().x + textPadding.x * 2;
    if (xSize < minSize.x )
    {
        xSize = minSize.x;
    } else if (haveMaxSize && xSize > maxSize.x)
    {
        xSize = maxSize.x;
    }
    float ySize = text.GetSize().y + textPadding.y * 2;
    if (ySize < minSize.y)
    {
        ySize = minSize.y;
    } else if ( haveMaxSize && ySize > maxSize.y)
    {
        ySize = maxSize.y;
    }
    
    SetSize({xSize, ySize});
}

void TextInput::OnUserText(char _char)
{
    if (GetSelectableState() != SelectableState::Selected) return;
    if (!ProcessCharInput(_char)) return;
    std::string newText = text.GetText()->getString();
    newText.insert(carretIndex, 1, _char);
    SetText(newText);
}

void TextInput::SetText(const std::string& _newText)
{
    std::string oldText = text.GetText()->getString();
    text.SetText(_newText);
    IncreaseCarretIndex();
    
    if (sizeType == Adaptive)
    {
        AdaptSize();
    }
    else if (sizeType == Fixed)
    {
        if (text.GetSize().x > GetSize().x)
        {
            text.SetText(oldText);
        }
        if (text.GetSize().y > GetSize().y)
        {
            text.SetText(oldText);
        }
    }
    else if (sizeType == FixedNoBlock)
    {
    }
}

bool TextInput::ProcessCharInput(const char _char)
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





void TextInput::ChangeCursorToTextInput(ISelectable* _selectable)
{
    ChangeCursor(sf::Cursor::Type::Text);
}

void TextInput::ChangeCursorToDefault(ISelectable* _selectable)
{
    ChangeCursor(sf::Cursor::Type::Arrow);
}



void TextInput::SetSize(const sf::Vector2f& _size)
{
    background.setSize(_size);
}

void TextInput::ChangeColor(sf::Color _newColor, SelectableState _newState)
{
    if (_newState == SelectableState::Disabled)
    {
        isBackgroundVisible = false;
    } else
    {
        isBackgroundVisible = true;
    }
    
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
    if (!isInitialized) return;

    float minDistance = 1000000;
    int minIndex = -1;
    float maxDistanceAccepted = 1000;
    for (int i = 0; i < text.GetText()->getString().getSize(); ++i)
    {
        float distance = MyMath::DistanceBetweenTwoPoints(text.GetText()->findCharacterPos(i), Input::GetMousePosition());
        if (distance < minDistance)
        {
            minDistance = distance;
            minIndex = i;
        }
    }
    if (minIndex != -1 && minDistance < maxDistanceAccepted)
    {
        ChangeCarretIndex(minIndex);
    }
    else
    {
        ChangeCarretIndex(text.GetText()->getString().getSize());
    }
    isCarretVisible = true;
}

void TextInput::UpdateCarretPosition()
{
    sf::Vector2f lastLetterPosition;
    if (!text.GetText()->getString().isEmpty())
    {
        lastLetterPosition = text.GetText()->findCharacterPos(carretIndex);
    } else
    {
        lastLetterPosition = sf::Vector2f(GetPosition().x + carretLeftPadding, GetPosition().y + (background.getSize().y - carret.getSize().y) / 2);
    }
    carret.setPosition(lastLetterPosition + sf::Vector2f(carretLeftPadding,0));
}

void TextInput::ChangeCarretIndex(int _newIndex)
{
    carretIndex = _newIndex;
    //UpdateCarretPosition();
}

void TextInput::IncreaseCarretIndex()
{
    carretIndex += 1;
    if (carretIndex > text.GetText()->getString().getSize())
    {
        carretIndex = text.GetText()->getString().getSize();
    }
    //UpdateCarretPosition();
}
void TextInput::DecreaseCarretIndex()
{
    carretIndex -= 1;
    if (carretIndex < 0)
    {
        carretIndex = 0;
    }
    //UpdateCarretPosition();
}

