#pragma once
#include "../../Headers/Components/Camera.h"
#include "../../Headers/Components/DrawableComponent.h"
#include "../../Headers/Scenes/Scene.h"
#include "../../Headers/Engine/GameObject.h"
Camera::Camera()
{
	SerializeField(sf::Vector2f, CameraView)
	SerializeField(sf::FloatRect, CameraRect)
}

// void Camera::Render()
// {
// 	window->clear(sf::Color::White);
// 	if (gameObject == nullptr)
// 	{
// 		std::cout << "CAMERA NOT INITIALIZED" << std::endl;
// 		return; 
// 	}
// 	for (auto& _gameObject: *scene->GetGameObjects())
// 	{
// 		for (auto& drawableLayer : *_gameObject->GetDrawableComponents())
// 		{
// 			for (auto& drawableComponent : drawableLayer.drawableComponents)
// 			{
// 				if (drawableComponent == nullptr) continue;
// 				if (drawableComponent->GetDrawable() == nullptr) continue;
// 				
// 				if (!IsOnDisplay(drawableComponent->GetAttachedObject()))
// 				{
// 					continue;
// 				}
// 				if (_gameObject->positionType != PositionType::UI)
// 				{
// 					drawableComponent->setPosition(drawableComponent->GetAttachedObject()->GetPosition() - gameObject->GetPosition());
// 				}
// 				window->draw(*drawableComponent->GetDrawable());
// 			}
// 			
// 		}
// 	}
//
// 	for (auto& [toDraw, attachedObj] : PermanentDrawablesObjects)
// 	{
// 		if (attachedObj != nullptr)
// 		{
// 			if (!IsOnDisplay(attachedObj))
// 			{
// 				continue;
// 			}
//
// 			toDraw->setPosition(attachedObj->GetPosition() - gameObject->GetPosition());
// 		}
// 		if (toDraw == nullptr) continue;
// 		window->draw(*toDraw);
// 	}
//
// 	for (int i = 0; i < Texts.size(); i++)
// 	{
// 		if (Texts[i] == nullptr) continue;
// 		window->draw(*Texts[i]);
//
// 	}
//
// 	window->display();
// }

void Camera::AddToPermanentDrawablesObjects(sf::Shape* drawableToAdd, GameObject* attachedObject)
{
	PermanentDrawablesObjects[drawableToAdd] = attachedObject;
}

void Camera::RemoveFromPermanentDrawablesObjects(sf::Shape* drawableToRemove)
{
	if (PermanentDrawablesObjects.contains(drawableToRemove))
	{
		PermanentDrawablesObjects.erase(drawableToRemove);
	}
}

void Camera::AddToTexts(sf::Text* textToAdd)
{
	Texts.push_back(textToAdd);
}

void Camera::RemoveFromTexts(sf::Text* textToRemove)
{
	for (int i = 0; i < Texts.size(); i++)
	{
		if (Texts[i] == textToRemove)
		{
			Texts.erase(Texts.begin() + i);
			return;
		}
	}
}

sf::RenderWindow* Camera::GetCurrentWindow()
{
	return window;
}

void Camera::UpdateCameraRect()
{
	CameraRect.left = gameObject->GetPosition().x;
	CameraRect.top = gameObject->GetPosition().y;
	CameraRect.width = CameraView.x;
	CameraRect.height = CameraView.y;
}

void Camera::Start()
{
}

void Camera::Update(float deltaTime)
{
	UpdateCameraRect();
	//Render();
}

void Camera::Init(sf::Vector2f _cameraView, sf::RenderWindow* _window)
{
	CameraView = _cameraView;
	window = _window; 
	componentWorkType = ComponentWorkType::PlayAndEditor;
}

sf::FloatRect Camera::GetCameraRect()
{
	return CameraRect;
}


