#pragma once
#include <ostream>
#include <SFML/System/Vector2.hpp>


class Vector2D
{
    friend std::ostream& operator<<(std::ostream& _os, const Vector2D& _obj)
    {
        return _os
            << "x: " << _obj.x
            << " y: " << _obj.y;
    }

public:
    Vector2D(float _x, float _y) : x(_x), y(_y) {}
    Vector2D() : x(0), y(0) {}
    Vector2D (sf::Vector2f _vector) : x(_vector.x), y(_vector.y) {}
    
    float x;
    float y;
};
