#pragma once
#include <string>
#include <fstream>

#include "../SerializeBuffer.h"
#include "../Engine/GameObject.h"
#include "../GameSystem/GameSystem.h"
#include "../Utilities/FileUtilities.h"
class Scene;



class SceneFileEditor : public GameSystem{
public:
	SceneFileEditor();
	~SceneFileEditor() override;
	AddType(SceneEditor, GameSystem::GetStaticType())
	
	bool CreateNewScene() const;
	void LoadScene() const;
	void SaveScene() const;
	
	std::string sceneName;
	std::string GetScenePath() const;

	//void CreateGameObject(GameObject* _gameObject) const;

	template<isObject T>
	void CreateObject(T* _object) const;


	void SetCurrentScene(Scene* _scene);
	Scene* GetCurrentScene() const;

	std::string GetSceneName() const;
private:
	static std::string scenePath;
	static std::string sceneFileExtension;
	Scene* level;
	
	const std::string NEWLINE_PREFIX = "--- ";
	const std::string TYPE_PREFIX = "!t!";
	const std::string ID_PREFIX = "!i!";
	
};

template <isObject T = Object>
void SceneFileEditor::CreateObject(T* _object) const
{
	if (level == nullptr)
	{
		return;
	}
	Object* obj = dynamic_cast<Object*>(_object);
	std::string newContent =
		NEWLINE_PREFIX + TYPE_PREFIX + std::to_string(GameObject::GetStaticType()->GetId()) + ID_PREFIX +
		std::to_string(_object->GetId()) + "\n";
	
	std::fstream file;
	file.open(GetScenePath(), std::ios::app);

	SerializeBuffer buffer;
	
	
	if (file.is_open())
	{
		file << newContent << *obj << "\n";

		if (GameObject* _go = dynamic_cast<GameObject*>(obj))
		{
			std::cout << "GameObject: " << _go->GetName() << " created" << std::endl;
			std::cout << *_go << std::endl;
		}
		
		file.close();
	}
	
}
