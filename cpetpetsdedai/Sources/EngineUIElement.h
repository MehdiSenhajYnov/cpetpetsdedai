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
    EngineUIElement(const uint64_t& _id, const std::string& _name, Type* parentType): Object(_id, _name, parentType) {}
    EngineUIElement(uint64_t _id): EngineUIElement(_id, "EngineUIElement", Object::GetStaticType()) {}
public:
    AddType(EngineUIElement, Object)
    virtual void Init(sf::RenderWindow* _window, sf::Cursor* _cursor)
    {
        window = _window;
        cursor = _cursor;
        isInitialized = true;
    }
    
    virtual void Draw(sf::RenderWindow* window) = 0;
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

protected:
    sf::Cursor::Type currentCursor = sf::Cursor::Type::Arrow;
    
    bool isInitialized = false;
    sf::RenderWindow* window = nullptr;
    sf::Cursor* cursor = nullptr;

    sf::Vector2f position = { 0.0f, 0.0f };
};
