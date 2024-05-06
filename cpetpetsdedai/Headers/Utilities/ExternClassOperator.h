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

inline std::ostream& operator<<(std::ostream& _os, const sf::Color& _obj) {
	return _os
				<< "a: " << _obj.a
				<< " r: " << _obj.r
				<< " g: " << _obj.g
				<< " b: " << _obj.b;
}
