#pragma once
#include <string>
#include "../GameSystem/GameSystem.h"

class SceneEditor : GameSystem{
public:
	SceneEditor();
	~SceneEditor() override;
	AddType(SceneEditor, GameSystem::GetStaticType())
	
	bool CreateNewScene(std::string _sceneName);
	void LoadScene(std::string _sceneName);
	std::string sceneName;
	std::string GetScenePath(std::string _sceneName);
private:
	static std::string scenePath;
	static std::string sceneFileExtension;
	
};
