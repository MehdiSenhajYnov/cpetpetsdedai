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

inline std::istream& operator>>(std::istream& _is, sf::Vector2f& _vec) {
	std::string temp;
	_is >> temp;
	_is >> _vec.x;
	_is >> temp;
	_is >> _vec.y;
	return _is;
}

inline std::ostream& operator<<(std::ostream& _os, const sf::Color& _obj) {
	return _os
				<< "a: " << std::to_string(_obj.a)
				<< " r: " << std::to_string(_obj.r)
				<< " g: " << std::to_string(_obj.g)
				<< " b: " << std::to_string(_obj.b);
}

inline std::istream& operator>>(std::istream& _is, sf::Color& _color) {
	std::string temp;

	_is >> temp;
	int colorInt = 0;
	_is >> colorInt;
	_color.a = colorInt;

	_is >> temp;
	_is >> colorInt;
	_color.r = colorInt;

	_is >> temp;
	_is >> colorInt;
	_color.g = colorInt;

	_is >> temp;
	_is >> colorInt;
	_color.b = colorInt;
	
	return _is;
}

inline std::ostream& operator<<(std::ostream& _os, const sf::FloatRect& _obj) {
	return _os
				<< "left: " << _obj.left
				<< " top: " << _obj.top
				<< " width: " << _obj.width
				<< " height: " << _obj.height;
}

inline std::istream& operator>>(std::istream& _is, sf::FloatRect& _rect) {
	std::string temp;
	
	_is >> temp;
	_is >> _rect.left;

	_is >> temp;
	_is >> _rect.top;

	_is >> temp;
	_is >> _rect.width;

	_is >> temp;
	_is >> _rect.height;

	return _is;
}
