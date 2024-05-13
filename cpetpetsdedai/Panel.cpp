#include "Panel.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>

#include "Headers/Input/Input.h"

Panel::Panel(): Panel("Panel", EngineUIElement::GetStaticType())
{ }

Panel::Panel(const std::string& _typeName, Type* parentType): EngineUIElement(_typeName, parentType)
{ }


Panel::Panel(uint64_t _id): Panel(_id, "Panel", EngineUIElement::GetStaticType())
{}

Panel::Panel(const uint64_t& _id, const std::string& _name, Type* parentType): EngineUIElement(_id, _name, parentType)
{}


void Panel::Init(sf::RenderWindow* _window, sf::Cursor* _cursor)
{
    EngineUIElement::Init(_window, _cursor);
    text.Init(_window, _cursor);
    
    line[0].color = sf::Color::Red;
    line[1].color = sf::Color::Red;

    SetName(GetType()->GetName());
    HoldSpace(text.GetSize());
}

void Panel::DragLine()
{
    if (isDragging)
    {
        if (GetAnchorSide() == Left)
        {
            float newLinePosX = (float)sf::Mouse::getPosition(*window).x - mouseOffset;
            SetSize(newLinePosX);
        } else if (GetAnchorSide() == Right)
        {
            float newLinePosX = (float)sf::Mouse::getPosition(*window).x - mouseOffset;
            SetSize((float)window->getSize().x - newLinePosX);
        } else if (GetAnchorSide() == Top)
        {
            float newLinePosY = (float)sf::Mouse::getPosition(*window).y - mouseOffset;
            SetSize(newLinePosY);
        } else if (GetAnchorSide() == Bottom)
        {
            float newLinePosY = (float)sf::Mouse::getPosition(*window).y - mouseOffset;
            SetSize((float)window->getSize().y - newLinePosY);
        }
    }
}

void Panel::MouseCursor()
{
    if (GetDirection() == Direction::Vertical)
    {
        if ((float)sf::Mouse::getPosition(*window).x > GetPosition().x - mouseHoverMarge && (float)sf::Mouse::getPosition(*window).x < GetPosition().x + mouseHoverMarge)
        {
            if (currentCursor != sf::Cursor::Type::SizeHorizontal)
            {
                ChangeCursor(sf::Cursor::Type::SizeHorizontal);
            }
        } else
        {
            if (currentCursor != sf::Cursor::Type::Arrow)
            {
                ChangeCursor(sf::Cursor::Type::Arrow);
            }
        }
    } else
    {
        if ((float)sf::Mouse::getPosition(*window).y > GetPosition().y - mouseHoverMarge && (float)sf::Mouse::getPosition(*window).y < GetPosition().y + mouseHoverMarge)
        {
            if (currentCursor != sf::Cursor::Type::SizeVertical)
            {
                ChangeCursor(sf::Cursor::Type::SizeVertical);
            }
        } else
        {
            if (currentCursor != sf::Cursor::Type::Arrow)
            {
                ChangeCursor(sf::Cursor::Type::Arrow);
            }
        }
    }
}



void Panel::Update(float _deltaTime)
{
    if (!isInitialized) return;
    if (window == nullptr) return;

    if (Input::GetKeyDown(KeyCode::LeftMouse))
    {
        OnMouseLeftKeyDown();
    }
    if (Input::GetKeyUp(KeyCode::LeftMouse))
    {
        OnMouseLeftKeyUp();
    }
    
    UpdateLinePos();
    text.SetPosition(GetPosition() + textPadding);
    DragLine();
    MouseCursor();

    text.Update(_deltaTime);
}

void Panel::Draw(sf::RenderWindow* _window)
{
    text.Draw(_window);
	_window->draw(line, 2, sf::Lines);
}

void Panel::SetName(const std::string& _name)
{
    name = _name;
    text.SetText(_name);
}

void Panel::OnMouseLeftKeyDown()
{

    if (currentCursor == sf::Cursor::Type::SizeHorizontal)
    {
        isDragging = true;
        mouseOffset = (float)sf::Mouse::getPosition(*window).x - GetPosition().x;
    } else if (currentCursor == sf::Cursor::Type::SizeVertical)
    {
        isDragging = true;
        mouseOffset = (float)sf::Mouse::getPosition(*window).y - GetPosition().y;
    }
}

void Panel::OnMouseLeftKeyUp()
{
    isDragging = false;
}

Direction Panel::GetDirection() const
{
    if (anchorSide == AnchorSide::Left || anchorSide == AnchorSide::Right)
    {
        return Direction::Vertical;
    } else
    {
        return Direction::Horizontal;
    }
}

sf::Vector2f Panel::GetAvaiblePosition() const
{
    return rawAvaiblePosition + GetPosition();
}

void Panel::HoldSpace(sf::Vector2f spaceHolded)
{
    if (GetDirection() == Direction::Vertical)
    {
        rawAvaiblePosition.y += spaceHolded.y + textPadding.y;
    } else if (GetDirection() == Direction::Horizontal)
    {
        rawAvaiblePosition.x += spaceHolded.x + textPadding.x;
    }
}

void Panel::ResetSpaceHolded()
{
    rawAvaiblePosition = { 0.0f, 0.0f };
    HoldSpace(text.GetSize());
}

void Panel::SetSize(float _size)
{
    size = _size;
    UpdateLinePos();
    
}

void Panel::UpdateLinePos()
{
    switch (GetAnchorSide())
    {
    case Left:
        line[0].position = sf::Vector2f(GetSize(), 0);
        line[1].position = sf::Vector2f(GetSize(), (float)window->getSize().y);
        break;
    case Right:
        line[0].position = sf::Vector2f(((float)window->getSize().x)- GetSize(), 0);
        line[1].position = sf::Vector2f(((float)window->getSize().x)- GetSize(), (float)window->getSize().y);
        break;
    case Top:
        line[0].position = sf::Vector2f(0, GetSize());
        line[1].position = sf::Vector2f((float)window->getSize().x, GetSize());
        break;
    case Bottom:
        line[0].position = sf::Vector2f(0, ((float)window->getSize().y)-GetSize());
        line[1].position = sf::Vector2f((float)window->getSize().x, ((float)window->getSize().y)-GetSize());
        break;
    }
    SetPosition(line[0].position);
}
