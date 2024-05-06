#include "RendererManager.h"

#include "CameraManager.h"
#include "EngineUI.h"
#include "TextComponent.h"
#include "Headers/Components/DrawableComponent.h"
#include "Headers/Engine/GameObject.h"

RendererManager* RendererManager::instance;


void RendererManager::Init(sf::RenderWindow* _window)
{
	window = _window;
}

void RendererManager::Clear()
{
	window->clear(sf::Color::White);
	drawableLayers.clear();
}

void RendererManager::Draw()
{
	fordebug.clear();
	for(auto& drawableLayer : drawableLayers)
	{
		for(auto& drawableComponent : drawableLayer.drawableComponents)
		{
			if (drawableComponent == nullptr) continue;
			if (drawableComponent->GetAttachedObject() == nullptr) continue;
			if (!drawableComponent->GetAttachedObject()->GetIsActive()) continue;

			GameObject* parent = drawableComponent->GetAttachedObject()->GetParent();
			bool parentIsNotActive = false;
			while(parent != nullptr)
			{
				if (!parent->GetIsActive())
				{
					parentIsNotActive = true;
					break;
				}
				parent = parent->GetParent();
			}
			
			if (drawableComponent->GetDrawable() == nullptr) continue;
			if (!isOnDisplay(drawableComponent))
			{
				continue;
			}
			
			if (drawableComponent->GetAttachedObject()->positionType != PositionType::UI)
			{
				drawableComponent->setPosition(drawableComponent->GetOffsetPosition() +
					drawableComponent->GetAttachedObject()->GetPosition() - CameraManager::GetInstance()->GetMainCamera()->GetAttachedObject()->GetPosition());
			} else
			{
				drawableComponent->setPosition(drawableComponent->GetOffsetPosition() + drawableComponent->GetAttachedObject()->GetPosition());
			}

			sf::Vector2f scaleToSet = {
				drawableComponent->GetScale().x * drawableComponent->GetAttachedObject()->GetScale().x,
				drawableComponent->GetScale().y * drawableComponent->GetAttachedObject()->GetScale().y
			};
			
			drawableComponent->SetDrawScale(scaleToSet);

			window->draw(*drawableComponent->GetDrawable());
		}
	}

	for (auto& element : fordebug)
	{
		window->draw(element);
	}

	DrawEngineUI();
	
	window->display();
}

void RendererManager::DrawEngineUI()
{
	for (auto& _uiElement : EngineUI::GetInstance()->GetUIElements())
	{
		if (_uiElement == nullptr) continue;
		_uiElement->Draw(window);
	}
	
}


void RendererManager::AddDrawableLayer(DrawableComponent* _drawableComponent)
{
	bool found = false;
	for(int i = 0; i < drawableLayers.size(); ++i)
	{
		if (drawableLayers[i].ZIndex == _drawableComponent->ZIndex)
		{
			drawableLayers[i].drawableComponents.push_back(_drawableComponent);
			found = true;
			return;
		}
		if (drawableLayers[i].ZIndex > _drawableComponent->ZIndex)
		{
			drawableLayers.insert(drawableLayers.begin() + i, DrawableLayer());
			drawableLayers[i].ZIndex = _drawableComponent->ZIndex;
			drawableLayers[i].drawableComponents.push_back(_drawableComponent);
			found = true;
			return;
		}
	}
	
	if (!found)
	{
		drawableLayers.push_back(DrawableLayer());
		drawableLayers[drawableLayers.size() - 1].ZIndex = _drawableComponent->ZIndex;
		drawableLayers[drawableLayers.size() - 1].drawableComponents.push_back(_drawableComponent);
	}
	
}

RendererManager* RendererManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new RendererManager();
	}
	return instance;
}

void RendererManager::ResetInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}

bool RendererManager::isOnDisplay(DrawableComponent* toCheck)
{
	return toCheck->GetBounds().intersects(CameraManager::GetInstance()->GetMainCamera()->GetCameraRect());
}
