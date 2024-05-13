#pragma once
#include <functional>
#include <sstream>
#include <string>
#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include "AllConcepts.h"

enum InBoundsInputType
{
    TopLeft,
    Center
};

class Utilities
{
public:
    static sf::Vector2f ScreenToWorld(sf::Vector2f screenPosition, sf::Vector2f cameraPosition, sf::Vector2f windowSize);
    static sf::Vector2f WorldToScreen(sf::Vector2f worldPosition, sf::Vector2f cameraPosition, sf::Vector2f windowSize);

    static std::string VectorToString(sf::Vector2f toconvert);
    
    static std::vector<std::string> SplitString(const std::string& _stringToSplit, const std::string& _delimiter);
    static int IndexOf(std::string _fullString, std::string _subString);

    static bool IsInBounds(const sf::Vector2f& _positionToCheck, const sf::Vector2f& _position, const sf::Vector2f& _size);
    static bool IsInBounds(const sf::Vector2f& _positionToCheck, const sf::Vector2f& _position, const sf::Vector2f& _size, InBoundsInputType _inputType);

    template <CanString T>
    static std::string ToString(const T& _value);
    
    static uint64_t GenerateUniqueId();

    static uint64_t Hash(std::string str);
};

template <CanString T>
std::string Utilities::ToString(const T& _value)
{
    std::ostringstream ss;
    ss << _value;
    return ss.str();
}
