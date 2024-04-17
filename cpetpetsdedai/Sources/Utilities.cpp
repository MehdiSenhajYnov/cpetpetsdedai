#include "../Headers/Utilities.h"

sf::Vector2f Utilities::ScreenToWorld(sf::Vector2f screenPosition, sf::Vector2f cameraPosition, sf::Vector2f windowSize)
{
    return {
        screenPosition.x + cameraPosition.x - windowSize.x / 2,
        screenPosition.y + cameraPosition.y - windowSize.y / 2
    };
}

sf::Vector2f Utilities::WorldToScreen(sf::Vector2f worldPosition, sf::Vector2f cameraPosition, sf::Vector2f windowSize)
{
    return {
        worldPosition.x - cameraPosition.x + windowSize.x / 2,
        worldPosition.y - cameraPosition.y + windowSize.y / 2
    };
}

std::string Utilities::VectorToString(sf::Vector2f toconvert)
{
    return "x : " + std::to_string(toconvert.x) + " y : " + std::to_string(toconvert.y); 
}
