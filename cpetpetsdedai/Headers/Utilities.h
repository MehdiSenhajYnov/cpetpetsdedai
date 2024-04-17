#pragma once
#include <string>
#include <SFML/System/Vector2.hpp>
class Utilities
{
public:
    static sf::Vector2f ScreenToWorld(sf::Vector2f screenPosition, sf::Vector2f cameraPosition, sf::Vector2f windowSize);
    static sf::Vector2f WorldToScreen(sf::Vector2f worldPosition, sf::Vector2f cameraPosition, sf::Vector2f windowSize);

    static std::string VectorToString(sf::Vector2f toconvert);
    
};
