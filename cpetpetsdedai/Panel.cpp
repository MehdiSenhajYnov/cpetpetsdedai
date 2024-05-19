#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Mouse.hpp>
#include "Panel.h"
#include "Headers/Input/Input.h"

Panel::Panel(): Panel("Panel", EngineUIElement::GetStaticType())
{ }

Panel::Panel(const std::string& _typeName, Type* parentType): EngineUIElement(_typeName, parentType)
{ }

Panel::~Panel()
{
    Factory::GetInstance()->DestroyObject(text);
}

void Panel::Init(sf::RenderWindow* _window)
{
    EngineUIElement::Init(_window);
    text = Factory::GetInstance()->CreateObject<TextUIElement>();
    text->Init(_window);
    
    line[0].color = sf::Color::Red;
    line[1].color = sf::Color::Red;

    SetName(GetType()->GetName());
    HoldSpace(text->GetSize());
}

void Panel::DragLine()
{
    if (isDragging)
    {
        if (GetAnchorSide() == Left)
        {
            float newLinePosX = (float)sf::Mouse::getPosition(*window).x - mouseOffset;
            SetPanelWidth(newLinePosX);
        } else if (GetAnchorSide() == Right)
        {
            float newLinePosX = (float)sf::Mouse::getPosition(*window).x - mouseOffset;
            SetPanelWidth((float)window->getSize().x - newLinePosX);
        } else if (GetAnchorSide() == Top)
        {
            float newLinePosY = (float)sf::Mouse::getPosition(*window).y - mouseOffset;
            SetPanelWidth(newLinePosY);
        } else if (GetAnchorSide() == Bottom)
        {
            float newLinePosY = (float)sf::Mouse::getPosition(*window).y - mouseOffset;
            SetPanelWidth((float)window->getSize().y - newLinePosY);
        }
    }
}

void Panel::MouseCursor()
{
    if (GetDirection() == Direction::Vertical)
    {
        if ((float)sf::Mouse::getPosition(*window).x > GetPosition().x - mouseHoverMarge && (float)sf::Mouse::getPosition(*window).x < GetPosition().x + mouseHoverMarge)
        {
            if (mouseHover != HorizontalSize)
            {
                ChangeCursor(sf::Cursor::Type::SizeHorizontal);
                mouseHover = HorizontalSize;
            }
        } else
        {
            if (mouseHover != None)
            {
                ChangeCursor(sf::Cursor::Type::Arrow);
                mouseHover = None;
            }
        }
    } else
    {
        if ((float)sf::Mouse::getPosition(*window).y > GetPosition().y - mouseHoverMarge && (float)sf::Mouse::getPosition(*window).y < GetPosition().y + mouseHoverMarge)
        {
            if (mouseHover != VerticalSize)
            {
                ChangeCursor(sf::Cursor::Type::SizeVertical);
                mouseHover = VerticalSize;
            }
        } else
        {
            if (mouseHover != None)
            {
                ChangeCursor(sf::Cursor::Type::Arrow);
                mouseHover = None;
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
    text->SetPosition(GetPosition() + textPadding);
    DragLine();
    MouseCursor();

    text->Update(_deltaTime);
}

void Panel::Draw(sf::RenderWindow* _window)
{
    text->Draw(_window);
	_window->draw(line, 2, sf::Lines);
}

void Panel::SetName(const std::string& _name)
{
    name = _name;
    text->SetText(_name);
}

void Panel::OnMouseLeftKeyDown()
{

    if (mouseHover == HorizontalSize)
    {
        isDragging = true;
        mouseOffset = (float)sf::Mouse::getPosition(*window).x - GetPosition().x;
    } else if (mouseHover == VerticalSize)
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
    HoldSpace(text->GetSize());
}

void Panel::SetPanelWidth(float _size)
{
    size = _size;
    UpdateLinePos();
    
}

void Panel::UpdateLinePos()
{
    switch (GetAnchorSide())
    {
    case Left:
        line[0].position = sf::Vector2f(GetPanelWidth(), 0);
        line[1].position = sf::Vector2f(GetPanelWidth(), (float)window->getSize().y);
        break;
    case Right:
        line[0].position = sf::Vector2f(((float)window->getSize().x)- GetPanelWidth(), 0);
        line[1].position = sf::Vector2f(((float)window->getSize().x)- GetPanelWidth(), (float)window->getSize().y);
        break;
    case Top:
        line[0].position = sf::Vector2f(0, GetPanelWidth());
        line[1].position = sf::Vector2f((float)window->getSize().x, GetPanelWidth());
        break;
    case Bottom:
        line[0].position = sf::Vector2f(0, ((float)window->getSize().y)-GetPanelWidth());
        line[1].position = sf::Vector2f((float)window->getSize().x, ((float)window->getSize().y)-GetPanelWidth());
        break;
    }
    SetPosition(line[0].position);
}
