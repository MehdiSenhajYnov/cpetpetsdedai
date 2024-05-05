#pragma once
#include <string>

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
	void LoadScene();
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

template <isObject T>
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

	
	for (auto& _field : obj->GetType()->GetAllFields())
	{
		newContent += _field->name + ": " + _field->GetValueAsString() + "\n";
	}
		
	
	FileUtilities::AppendInFile(GetScenePath(), newContent);
}
