#pragma once
#include "Headers/Engine/Object.h"

class Camera;
// SINGLETON
class CameraManager : public Object{
public:
	ADD_TYPE(CameraManager, Object, REG_TYPE);
	static CameraManager* GetInstance();

	static void ResetInstance();

	Camera*GetMainCamera() const;
	void SetMainCamera(Camera* camera);
	void AddCamera(Camera* camera);
	void RemoveCamera(Camera* camera);
	TList<Camera*>* GetCameras();

private:
	Camera* mainCamera = nullptr;
	TList<Camera*> cameras;
	CameraManager();

};
