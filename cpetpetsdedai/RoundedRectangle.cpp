#include "RoundedRectangle.h"


void RoundedRectangle::Init(float _width, float _height, float _radius, int accuracy)
{
    width = _width;
    height = _height;
    radius = _radius;

    
    roundedRectangleShape.setPointCount(4 * accuracy); // 4 points per corner, each with specified accuracy

    // Calculating the number of points per arc
    int pointsPerArc = accuracy / 4;

    // Setting up the initial variables
    float angle = 90.0f;
    float x, y;

    // Loop to create the top-left corner
    for (int i = 0; i < pointsPerArc; ++i) {
        x = _radius * std::cos(angle * 3.14159265f / 180.0f);
        y = _radius * std::sin(angle * 3.14159265f / 180.0f);
        roundedRectangleShape.setPoint(i, sf::Vector2f(_radius + x, _radius + y));
        angle -= 90.0f / pointsPerArc;
    }

    // Loop to create the top-right corner
    for (int i = pointsPerArc; i < 2 * pointsPerArc; ++i) {
        x = _radius * std::cos(angle * 3.14159265f / 180.0f);
        y = _radius * std::sin(angle * 3.14159265f / 180.0f);
        roundedRectangleShape.setPoint(i, sf::Vector2f(_width - _radius + x, _radius + y));
        angle -= 90.0f / pointsPerArc;
    }

    // Loop to create the bottom-right corner
    for (int i = 2 * pointsPerArc; i < 3 * pointsPerArc; ++i) {
        x = _radius * std::cos(angle * 3.14159265f / 180.0f);
        y = _radius * std::sin(angle * 3.14159265f / 180.0f);
        roundedRectangleShape.setPoint(i, sf::Vector2f(_width - _radius + x, _height - _radius + y));
        angle -= 90.0f / pointsPerArc;
    }

    // Loop to create the bottom-left corner
    for (int i = 3 * pointsPerArc; i < 4 * pointsPerArc; ++i) {
        x = _radius * std::cos(angle * 3.14159265f / 180.0f);
        y = _radius * std::sin(angle * 3.14159265f / 180.0f);
        roundedRectangleShape.setPoint(i, sf::Vector2f(_radius + x, _height - _radius + y));
        angle -= 90.0f / pointsPerArc;
    }

    // Setting up the remaining sides
    roundedRectangleShape.setPoint(4 * pointsPerArc, sf::Vector2f(_radius, 0));
    roundedRectangleShape.setPoint(4 * pointsPerArc + 1, sf::Vector2f(_width - _radius, 0));
    roundedRectangleShape.setPoint(4 * pointsPerArc + 2, sf::Vector2f(_width, _radius));
    roundedRectangleShape.setPoint(4 * pointsPerArc + 3, sf::Vector2f(_width, _height - _radius));
    roundedRectangleShape.setPoint(4 * pointsPerArc + 4, sf::Vector2f(_width - _radius, _height));
    roundedRectangleShape.setPoint(4 * pointsPerArc + 5, sf::Vector2f(_radius, _height));
    roundedRectangleShape.setPoint(4 * pointsPerArc + 6, sf::Vector2f(0, _height - _radius));
    roundedRectangleShape.setPoint(4 * pointsPerArc + 7, sf::Vector2f(0, _radius));

    roundedRectangleShape.setFillColor(sf::Color::Green);
}

const sf::Drawable* RoundedRectangle::GetDrawable()
{
    return &roundedRectangleShape;
}

void RoundedRectangle::setPosition(sf::Vector2f pos)
{
    roundedRectangleShape.setPosition(pos);
}

sf::Vector2f RoundedRectangle::GetOriginalSize()
{
    return sf::Vector2f(width,height);}

sf::FloatRect RoundedRectangle::GetBounds()
{
    return roundedRectangleShape.getLocalBounds();
}

void RoundedRectangle::Start()
{
}


