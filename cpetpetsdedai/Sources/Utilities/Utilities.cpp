#pragma once
#include "../../Headers/Utilities/Utilities.h"

#include <random>

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

std::vector<std::string> Utilities::SplitString(std::string _stringToSplit, std::string _delimiter) {
    size_t pos_start = 0, pos_end, delim_len = _delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = _stringToSplit.find(_delimiter, pos_start)) != std::string::npos) {
        token = _stringToSplit.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (_stringToSplit.substr (pos_start));
    return res;
}

int Utilities::IndexOf(std::string _fullString, std::string _subString)
{
    size_t found = _fullString.find(_subString);
    if (found != std::string::npos)
    {
        return found;
    }
    return -1;
}

bool Utilities::IsInBounds(const sf::Vector2f& _positionToCheck, const sf::Vector2f& _position, const sf::Vector2f& _size)
{
    if (_positionToCheck.x < _position.x || _positionToCheck.x > _position.x + _size.x)
    {
        return false;
    }

    if (_positionToCheck.y < _position.y || _positionToCheck.y > _position.y + _size.y)
    {
        return false;
    }

    return true;
}

bool Utilities::IsInBounds(const sf::Vector2f& _positionToCheck, const sf::Vector2f& _position, const sf::Vector2f& _size, InBoundsInputType _inputType)
{
    if (_inputType == InBoundsInputType::TopLeft)
    {
        return IsInBounds(_positionToCheck, _position, _size);
    }
    
    if (_positionToCheck.x < _position.x - (_size.x/2)|| _positionToCheck.x > _position.x + (_size.x/2))
    {
        return false;
    }

    if (_positionToCheck.y < _position.y - (_size.y/2)|| _positionToCheck.y > _position.y + (_size.y/2))
    {
        return false;
    }

    return true;
}



unsigned int Utilities::GenerateUniqueId()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned int> dis(1, 99999999);
    return dis(gen);
}

uint64_t Utilities::Hash(std::string str)
{
    std::uint64_t hash_value = 0xcbf29ce484222325ULL;
    constexpr std::uint64_t prime = 0x100000001b3ULL;
    for (char c : str)
    {
        hash_value ^= static_cast<std::uint64_t>(c);
        hash_value *= prime;
    }
    return hash_value;
}
