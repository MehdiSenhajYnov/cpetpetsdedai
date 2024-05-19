#pragma once
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Cursor.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Mouse.hpp>

#include "../Headers/Engine/Object.h"

enum AnchorSide
{
    Left,
    Right,
    Top,
    Bottom
};


class EngineUIElement : public Object
{
protected:
    
    EngineUIElement() : EngineUIElement("EngineUIElement", Object::GetStaticType()) { }
    EngineUIElement(const std::string& _typeName, Type* parentType) : Object(_typeName, parentType) { }
public:
    ADD_TYPE(EngineUIElement, Object, REG_TYPE)
    virtual void Init(sf::RenderWindow* _window)
    {
        window = _window;
        isInitialized = true;
    }
    
    virtual void Draw(sf::RenderWindow* _window) = 0;
    virtual void Update(float _deltaTime) = 0;
    virtual void PreDestroy() {}
    
    virtual ~EngineUIElement() override = default;

    bool IsInitialized() const { return isInitialized; }

    virtual void OnKeyDown(sf::Keyboard::Key pressedKey) {}
    virtual void OnMouseKeyDown(sf::Mouse::Button pressedKey) {}
    virtual void OnMouseKeyUp(sf::Mouse::Button pressedKey) {}

    sf::Vector2f GetPosition() const { return position; }
    virtual void SetPosition(const sf::Vector2f& _position) { position = _position; }

    void ChangeCursor(sf::Cursor::Type cursorType);

    virtual sf::Vector2f GetSize() const { return size; }
    virtual sf::Vector2f GetOrigin() const { return origin; }

    virtual void SetSize(const sf::Vector2f& _size) { size = _size; }
    virtual void SetOrigin(const sf::Vector2f& _origin) { origin = _origin; }

    bool GetIsInitialized() const { return isInitialized; }
protected:
    //sf::Cursor::Type currentCursor = sf::Cursor::Type::Arrow;
    
    bool isInitialized = false;
    sf::RenderWindow* window = nullptr;

    sf::Vector2f position = { 0.0f, 0.0f };

    sf::Vector2f size = { 0.0f, 0.0f };
    sf::Vector2f origin = { 0.0f, 0.0f };
};
