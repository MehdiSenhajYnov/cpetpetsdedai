#include "CameraManager.h"


CameraManager* CameraManager::GetInstance()
{
	static CameraManager* instance;

	if (instance == nullptr)
	{
		instance = new CameraManager();
	}
	return instance;
}

void CameraManager::ResetInstance()
{
	auto instance = GetInstance();
	delete instance;
	instance = nullptr;
}

Camera* CameraManager::GetMainCamera() const
{
	return mainCamera;
}

void CameraManager::SetMainCamera(Camera* camera)
{
	mainCamera = camera;
}

void CameraManager::AddCamera(Camera* camera)
{
	cameras.push_back(camera);
	if (mainCamera == nullptr)
	{
		SetMainCamera(camera);
	}
}

void CameraManager::RemoveCamera(Camera* camera)
{
	cameras.RemoveElement(camera);
	if (mainCamera == camera)
	{
		if (!cameras.empty())
		{
			SetMainCamera(cameras[0]);
		}
		else
		{
			SetMainCamera(nullptr);
		}
	}
}

TList<Camera*>* CameraManager::GetCameras()
{
	return &cameras;
}

CameraManager::CameraManager() : Object("CameraManager", Object::GetStaticType()), mainCamera(nullptr)
{
	
}
