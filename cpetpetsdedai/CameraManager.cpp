#include "CameraManager.h"

CameraManager* CameraManager::instance;

CameraManager* CameraManager::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new CameraManager();
	}
	return instance;
}

void CameraManager::ResetInstance()
{
	if(instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
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
}

void CameraManager::RemoveCamera(Camera* camera)
{
	cameras.RemoveElement(camera);
}

TList<Camera*>* CameraManager::GetCameras()
{
	return &cameras;
}

CameraManager::CameraManager() : Object("CameraManager", Object::GetStaticType()), mainCamera(nullptr)
{
	
}
