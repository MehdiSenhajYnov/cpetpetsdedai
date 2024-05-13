#pragma once
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>

inline sf::Vector2f operator/(const sf::Vector2f& _vectorToDivide, float _divideValue)
{
	return {_vectorToDivide.x / _divideValue, _vectorToDivide.y / _divideValue};
}

inline std::ostream& operator<<(std::ostream& _os, const sf::Vector2f& _obj) {
	return _os
				<< "x: " << _obj.x
				<< " y: " << _obj.y;
}

inline std::istream& operator>>(std::istream& is, sf::Vector2f& vec) {
	std::string temp;
	is >> temp;
	float _x = 0;
	float _y = 0;
	is >> vec.x;
	is >> temp;
	is >> vec.y;
	return is;
}

inline std::ostream& operator<<(std::ostream& _os, const sf::Color& _obj) {
	return _os
				<< "a: " << std::to_string(_obj.a)
				<< " r: " << std::to_string(_obj.r)
				<< " g: " << std::to_string(_obj.g)
				<< " b: " << std::to_string(_obj.b);
}

inline std::istream& operator>>(std::istream& is, sf::Color& color) {
	std::string str;
	is >> str;
	if (str.size() < 15)
		throw std::invalid_argument("Invalid input for sf::Color");
    
	if (str.substr(0, 2) != "a:" || str.substr(str.find("r:") - 1, 2) != "r:" ||
		str.substr(str.find("g:") - 1, 2) != "g:" || str.substr(str.find("b:") - 1, 2) != "b:")
		throw std::invalid_argument("Invalid input format for sf::Color");

	size_t aPos = str.find("a:") + 2;
	size_t rPos = str.find("r:") + 2;
	size_t gPos = str.find("g:") + 2;
	size_t bPos = str.find("b:") + 2;

	color.a = std::stoi(str.substr(aPos, rPos - aPos - 2));
	color.r = std::stoi(str.substr(rPos, gPos - rPos - 2));
	color.g = std::stoi(str.substr(gPos, bPos - gPos - 2));
	color.b = std::stoi(str.substr(bPos));

	return is;
}

inline std::ostream& operator<<(std::ostream& _os, const sf::FloatRect& _obj) {
	return _os
				<< "left: " << _obj.left
				<< " top: " << _obj.top
				<< " width: " << _obj.width
				<< " height: " << _obj.height;
}

inline std::istream& operator>>(std::istream& is, sf::FloatRect& rect) {
	std::string str;
	is >> str;
	if (str.size() < 25)
		throw std::invalid_argument("Invalid input for sf::FloatRect");
    
	if (str.substr(0, 5) != "left:" || str.substr(str.find("top:") - 1, 5) != " top:" ||
		str.substr(str.find("width:") - 1, 7) != " width:" || str.substr(str.find("height:") - 1, 8) != " height:")
		throw std::invalid_argument("Invalid input format for sf::FloatRect");

	size_t leftPos = str.find("left:") + 5;
	size_t topPos = str.find("top:") + 5;
	size_t widthPos = str.find("width:") + 7;
	size_t heightPos = str.find("height:") + 8;

	rect.left = std::stof(str.substr(leftPos, topPos - leftPos - 5));
	rect.top = std::stof(str.substr(topPos, widthPos - topPos - 7));
	rect.width = std::stof(str.substr(widthPos, heightPos - widthPos - 8));
	rect.height = std::stof(str.substr(heightPos));

	return is;
}
