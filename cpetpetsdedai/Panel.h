#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Vertex.hpp>

#include "TextComponent.h"
#include "TextUIElement.h"
#include "Headers/Engine/Object.h"
#include "Sources/EngineUIElement.h"

enum Direction
{
    Horizontal,
    Vertical
};

enum MouseHoverType
{
    None,
    HorizontalSize,
    VerticalSize,
};

class Panel : public EngineUIElement
{
public:
    Panel();
    Panel(const std::string& _typeName, Type* parentType);
    Panel(const uint64_t& _id, const std::string& _name, Type* parentType);
    Panel(uint64_t _id);
    virtual ~Panel() override;

    AddType(Panel, EngineUIElement)

    virtual void Init(sf::RenderWindow* _window) override;
    void DragLine();
    void MouseCursor();
    void Update(float _deltaTime) override;
    void Draw(sf::RenderWindow* _window) override;

    TextUIElement* text;
    std::string GetName() const { return name; }
    virtual void SetName(const std::string& _name);

    
    void OnMouseLeftKeyDown();
    void OnMouseLeftKeyUp();
    
    Direction GetDirection() const;

    sf::Vector2f GetAvaiblePosition() const;
    virtual void HoldSpace(sf::Vector2f spaceHolded);
    virtual void ResetSpaceHolded();

    AnchorSide GetAnchorSide() const { return anchorSide; }
    void SetAnchorSide(AnchorSide _anchorSide) { anchorSide = _anchorSide; }

    
    float GetSize() const { return size; }
    void SetSize(float _size);

protected:
    float size = 300.0f;
    AnchorSide anchorSide = AnchorSide::Left;
    std::string name;

private:
    void UpdateLinePos();

private:
    sf::Vertex line[2];
    
    float mouseHoverMarge = 10.0f;

    MouseHoverType mouseHover = None;
    bool isDragging = false;
    float mouseOffset = 0.0f;

    sf::Vector2f textPadding = { 5.0f, 5.0f };

    Direction contentOrientation = GetDirection();

    sf::Vector2f rawAvaiblePosition = { 0.0f, 0.0f };
};
