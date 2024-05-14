#pragma once
#include "../../Sources/EngineUIElement.h"

class VerticalList : public EngineUIElement{
public:
	AddType(VerticalList, EngineUIElement)
	
	
	template<typename T>
	void AddToContextMenu() requires IsBaseOf<EngineUIElement, T> && haveGetSize<T> && haveOrigin<T>
	{
		T* elementInstance = Factory::GetInstance()->CreateObject<T>();
		sf::Vector2f elementPosition = {0,0};
		if (elements.size() > 0)
		{
			elementPosition = currentBottomLeft + sf::Vector2f(0,  spaceBetweenButtons);
		}
		else
		{
			elementPosition = GetPosition();
			currentTopRight = GetPosition() + sf::Vector2f(elementInstance->GetSize().x, 0);
		}
		elementInstance->SetPosition(GetPosition() + elementInstance->GetPosition());
		currentBottomLeft = elementPosition + elementInstance->GetSize().y - elementInstance->GetOrigin().y;
		currentBottomRight = currentBottomLeft + elementInstance->GetSize().x;
		elements.push_back(elementInstance);
	}

	bool IsInside(sf::Vector2f _mousePosition)
	{
		if (_mousePosition.x > GetPosition().x && _mousePosition.x < currentTopRight.x && _mousePosition.y > GetPosition().y && _mousePosition.y < currentBottomLeft.y)
		{
			return true;
		}
		return false;
	}

	
private:
	TList<EngineUIElement*> elements;


	sf::Color baseColor = sf::Color(74, 74, 74);
	sf::Color hoverColor = sf::Color(100, 100, 100);
	sf::Color textColor = sf::Color::White;

	float spaceBetweenButtons = 0;

	sf::Vector2f currentTopRight = {0,0};
	sf::Vector2f currentBottomLeft = {0,0};
	sf::Vector2f currentBottomRight = {0,0};
	
};
