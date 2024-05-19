#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include "../../Sources/EngineUIElement.h"

class ScrollbarUiElement : public EngineUIElement
{
public:
    void Draw(sf::RenderWindow* _window) override;
    void Update(float _deltaTime) override;
    void SetColor(const sf::Color& _color) ;
    void Init(sf::RenderWindow* _window) override;
    void SetSize(const sf::Vector2f& _size) override;
    void SetPosition(const sf::Vector2f& _position) override;

    void SetMinY(float _minY) { userMinY = _minY; }
    void SetMaxY(float _maxY) { userMaxY = _maxY; }
    void SetMinMaxY(float _minY, float _maxY)
    {
        userMinY = _minY;
        userMaxY = _maxY;
        minY = _minY + GetSize().y/2;
        maxY = _maxY - GetSize().y/2;
    }

    float GetMinY() const { return userMinY; }
    float GetMaxY() const { return userMaxY; }

    void SetActive(bool _active) { isActive = _active; }
    bool GetActive() const { return isActive; }

    float GetPercentage()
    {
        if (CheckFloatEquals(minY, maxY))
        {
            return 1;
        }
        return (scrollbar.getPosition().y - minY) / (maxY - minY);
    }

    void ResetY();

    Event<sf::Vector2f, float> OnPositionChanged;
    
private:
    bool isDragging = false;
    float yOffset = 0.0f;
    sf::RectangleShape scrollbar;
    sf::Color currentColor;
    sf::Color baseColor = sf::Color::Black;
    sf::Color hoverColor = sf::Color(120,120, 120);

    float userMinY = 200.0f;
    float userMaxY = 900.0f;
    float minY = 100.0f;
    float maxY = 1000.0f;
    bool isActive = true;

    bool CheckFloatEquals(float a, float b)
    {
        return fabs(a - b) < 0.001;
    }
};
