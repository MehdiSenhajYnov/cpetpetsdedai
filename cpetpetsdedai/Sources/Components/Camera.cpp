#pragma once
#include "../../Headers/Components/Camera.h"

#include "../../CameraManager.h"
#include "../../Headers/Components/DrawableComponent.h"
#include "../../Headers/Scenes/Scene.h"
#include "../../Headers/Engine/GameObject.h"

Camera::Camera() : Component("Camera", Component::GetStaticType())
{
	SERIALIZE_FIELD(CameraView)
	SERIALIZE_FIELD(CameraRect)
	CameraManager::GetInstance()->AddCamera(this);
}

Camera::~Camera()
{
	CameraManager::GetInstance()->RemoveCamera(this);
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

void Camera::Init(sf::Vector2f _cameraView)
{
	CameraView = _cameraView;
	componentWorkType = ComponentWorkType::PlayAndEditor;
}

sf::FloatRect Camera::GetCameraRect()
{
	return CameraRect;
}


