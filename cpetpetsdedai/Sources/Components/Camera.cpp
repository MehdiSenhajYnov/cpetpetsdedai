#pragma once
#include "../../Headers/Components/Camera.h"
#include "../../Headers/Components/DrawableComponent.h"
#include "../../Headers/Scenes/Scene.h"
#include "../../Headers/Engine/GameObject.h"
Camera::Camera()
{
}

void Camera::Render()
{
	window->clear(sf::Color::White);
	if (gameObject == nullptr)
	{
		std::cout << "CAMERA NOT INITIALIZED" << std::endl;
		return; 
	}
	for (auto& _gameObject: *scene->GetGameObjects())
	{
		for (auto& spriteRenderer : *_gameObject->GetDrawableComponents())
		{
			if (spriteRenderer == nullptr) continue;
			if (spriteRenderer->GetDrawable() == nullptr) continue;
			
			if (!IsOnDisplay(spriteRenderer->GetAttachedObject()))
			{
				continue;
			}
			if (_gameObject->positionType != PositionType::UI)
			{
				spriteRenderer->setPosition(spriteRenderer->GetAttachedObject()->GetPosition() - gameObject->GetPosition());
			}
			//std::cout << "drawing " << _gameObject->Name << std::endl;
			window->draw(*spriteRenderer->GetDrawable());
		}
	}

	for (auto& [toDraw, attachedObj] : PermanentDrawablesObjects)
	{
		if (attachedObj != nullptr)
		{
			if (!IsOnDisplay(attachedObj))
			{
				continue;
			}

			toDraw->setPosition(attachedObj->GetPosition() - gameObject->GetPosition());
		}
		if (toDraw == nullptr) continue;
		window->draw(*toDraw);
	}

	for (int i = 0; i < Texts.size(); i++)
	{
		if (Texts[i] == nullptr) continue;
		window->draw(*Texts[i]);

	}

	window->display();
}

bool Camera::IsOnDisplay(GameObject* toCheck)
{

	// TODO: add object scale and texture size
	if (toCheck->GetPosition().x < gameObject->GetPosition().x - CameraView.x ||
		toCheck->GetPosition().x > gameObject->GetPosition().x + CameraView.x)
	{
		return false;
	}

	if (toCheck->GetPosition().y < gameObject->GetPosition().y - CameraView.y ||
		toCheck->GetPosition().y > gameObject->GetPosition().y + CameraView.y)
	{
		return false;
	}

	return true;
}


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

void Camera::Start()
{
}

void Camera::Update(float deltaTime)
{
	Render();
}

void Camera::Init(sf::Vector2f _cameraView, sf::RenderWindow* _window, Scene* _scene)
{
	CameraView = _cameraView;
	window = _window; 
	scene = _scene;
	componentWorkType = ComponentWorkType::PlayAndEditor;
}


