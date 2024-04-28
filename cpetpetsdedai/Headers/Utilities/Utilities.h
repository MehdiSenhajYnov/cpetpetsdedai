#pragma once
#include <functional>
#include <string>
#include <vector>
#include <SFML/System/Vector2.hpp>

class Utilities
{
public:
    static sf::Vector2f ScreenToWorld(sf::Vector2f screenPosition, sf::Vector2f cameraPosition, sf::Vector2f windowSize);
    static sf::Vector2f WorldToScreen(sf::Vector2f worldPosition, sf::Vector2f cameraPosition, sf::Vector2f windowSize);

    static std::string VectorToString(sf::Vector2f toconvert);
    static std::vector<std::string> SplitString(std::string _stringToSplit, std::string _delimiter);

    static bool IsInBounds(const sf::Vector2f& _positionToCheck, const sf::Vector2f& _position, const sf::Vector2f& _size);
};
