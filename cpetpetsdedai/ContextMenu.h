#pragma once
#include "Headers/Engine/GameObject.h"
#include "Headers/Components/Button.h"
#include "Headers/Components/SpriteRenderer.h"
#include "Headers/Utilities/Utilities.h"
#include "TextComponent.h"
#include "Headers/Utilities/MyMath.h"

class ContextMenu : public GameObject{
public:
	ContextMenu() : GameObject("ContextMenu", GameObject::GetStaticType())
	{
		positionType = PositionType::UI;
	}
	AddType(ContextMenu, GameObject)

	
	template<typename Class>
	void AddToContextMenu(const std::string _name, void(Class::*_function)(Button*) , Class* instance)
	{
		Button* contextButton = AddComponent<Button>();
		contextButton->OnButtonClicked.Subscribe(_function, instance);

		SpriteRenderer* contextMenuBackgroundSpriteRenderer = AddComponent<SpriteRenderer>();
		contextMenuBackgroundSpriteRenderer->SetSprite("Square");
		contextMenuBackgroundSpriteRenderer->SetColor(baseColor);
		contextMenuBackgroundSpriteRenderer->SetZIndex(100);
	
		contextButton->Init(contextMenuBackgroundSpriteRenderer);
		contextButton->InitDefaultTextComponent(_name);
		contextButton->GetTextComponent()->SetFontSize(17);
		contextButton->GetTextComponent()->SetZIndex(101);
		
		sf::Vector2f textSize = contextButton->GetTextComponent()->GetCurrentSize();
		float wantedWidth = textSize.x + minPadding;

		if (wantedWidth > xScale)
		{
			currentWidth = wantedWidth;
			xScale = currentWidth * 0.01f;

			for (int i = 0; i < buttonsContainer.size(); ++i)
			{
				buttonsContainer[i]->GetSpriteRenderer()->SetScale({xScale, yScale});
			}
		}
		contextButton->GetSpriteRenderer()->SetScale({xScale, yScale});
		
		contextMenuBackgroundSpriteRenderer->SetOffsetPosition(sf::Vector2f(0, (height + spaceBetweenButtons) * buttonsContainer.size()));
		
		contextButton->SetBaseColor(baseColor);
		contextButton->SetHoverColor(hoverColor);
		contextButton->SetTextColor(textColor);
		
		buttonsContainer.push_back(contextButton);
	}

	bool IsInsideContextMenu(sf::Vector2f _mousePosition)
	{
		for(const auto& button : buttonsContainer)
		{
			if (Utilities::IsInBounds(_mousePosition, button->GetSpriteRenderer()->GetOffsetPosition() + GetPosition(),
				button->GetSpriteRenderer()->GetCurrentSize(), Center))
			{
				return true;
			}
		}
		return false;
	}

	float GetHeight() const
	{
		return height;
	}

	float GetFullHeight() const
	{
		return height * buttonsContainer.size() + spaceBetweenButtons * (buttonsContainer.size() - 1);
	}
	
	float GetWidth() const
	{
		return currentWidth;
	}
	

private:
	TList<Button*> buttonsContainer;
	float currentWidth = 0;
	float height = 30;

	float xScale = 0;
	float yScale = 0.3f;

	float minPadding = 20;
	float spaceBetweenButtons = 0;

	sf::Color baseColor = sf::Color(74, 74, 74);
	sf::Color hoverColor = sf::Color(100, 100, 100);
	sf::Color textColor = sf::Color::White;

};
