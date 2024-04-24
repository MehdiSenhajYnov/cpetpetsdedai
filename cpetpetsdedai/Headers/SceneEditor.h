#pragma once
#include <string>
#include "GameSystem.h"

class SceneEditor : GameSystem{
public:
	SceneEditor();
	~SceneEditor() override;
	
	bool CreateScene(std::string _sceneName);
	std::string sceneName;
	
private:
	static std::string scenePath;
	static std::string sceneFileExtension;
};
