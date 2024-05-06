#pragma once
#include "Headers/Components/Camera.h"

class CameraManager : public Object{
public:
	AddType(CameraManager, Object::GetStaticType());
	static CameraManager* GetInstance();

	static void ResetInstance();

	Camera*GetMainCamera() const;
	void SetMainCamera(Camera* camera);
	void AddCamera(Camera* camera);
	void RemoveCamera(Camera* camera);
	TList<Camera*>* GetCameras();

private:
	static CameraManager* instance;
	Camera* mainCamera;
	TList<Camera*> cameras;
	CameraManager();

};
