#pragma once
#include "Headers/Engine/GameObject.h"
#include "Headers/Components/Button.h"
#include "Headers/Components/SpriteRenderer.h"
#include "Headers/Utilities/Utilities.h"

class ContextMenu : public GameObject{
public:
	ContextMenu() : GameObject("ContextMenu", GameObject::GetStaticType())
	{
		SetScale(1, 0.3f);
		positionType = PositionType::UI;
	}
	AddType(ContextMenu, GameObject::GetStaticType())

	
	template<typename Class>
	void AddToContextMenu(std::string _name, void(Class::*_function)(Button*) , Class* instance)
	{
		Button* contextButton = AddComponent<Button>();
		contextButton->OnButtonClicked.Subscribe(_function, instance);

		SpriteRenderer* contextMenuBackgroundSpriteRenderer = AddComponent<SpriteRenderer>();
		contextMenuBackgroundSpriteRenderer->SetSprite("Square");
		contextMenuBackgroundSpriteRenderer->SetColor(sf::Color(200,200,200));
		contextMenuBackgroundSpriteRenderer->SetZIndex(100);
		contextMenuBackgroundSpriteRenderer->SetOffsetPosition(sf::Vector2f(0, contextMenuBackgroundSpriteRenderer->GetSize().y * buttonsContainer.size()));
	
		contextButton->Init(contextMenuBackgroundSpriteRenderer);
		buttonsContainer.push_back(contextButton);
	}

	bool IsInBounds(sf::Vector2f _mousePosition)
	{
		for (Button* _button : buttonsContainer)
		{
			if (Utilities::IsInBounds(_mousePosition, _button->GetSpriteRenderer()->GetOffsetPosition() + GetPosition(), _button->GetSize()))
			{
				return true;
			}
		}
		return false;
	}

private:
	TList<Button*> buttonsContainer;
};
