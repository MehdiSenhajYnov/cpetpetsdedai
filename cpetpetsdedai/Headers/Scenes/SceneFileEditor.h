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

	template <isSerialisable T = ISerialisable>
	void WriteObjectInFile(T* _object) const;
	template <isSerialisable T>
	static std::string GetObjectSerializePrefix(T* _object) ;
	

	void SetCurrentScene(Scene* _scene);
	Scene* GetCurrentScene() const;

	std::string GetSceneName() const;
private:
	static std::string scenePath;
	static std::string sceneFileExtension;
	Scene* level;
	
	static inline const std::string NEWLINE_PREFIX = "--- ";
	static inline const std::string TYPE_PREFIX = "!t!";
	static inline const std::string ID_PREFIX = "!i!";
	
};

template <isSerialisable T = ISerialisable>
void SceneFileEditor::WriteObjectInFile(T* _object) const
{
	if (level == nullptr)
	{
		return;
	}

	SerializeBuffer buffer;
	_object->Serialize(buffer);
	if (!buffer.startBuffer.str().empty())
	{
		FileUtilities::AppenInFileAtLine(GetScenePath(), buffer.startBuffer.str(), 0);
	}
	if (!buffer.mainBuffer.str().empty())
	{
		FileUtilities::AppendInFile(GetScenePath(), buffer.mainBuffer.str());
	}
	if (!buffer.endBuffer.str().empty())
	{
		FileUtilities::AppendInFile(GetScenePath(), buffer.endBuffer.str());
	}
	
	// std::fstream file;
	// file.open(GetScenePath(), std::ios::app);
	// if (file.is_open())
	// {
	//
	// 	file << SceneFileEditor::GetObjectSerializePrefix(_object) << *obj << "\n";
	// 	file.close();
	// }
	
}

template <isSerialisable T>
std::string SceneFileEditor::GetObjectSerializePrefix(T* _object)
{
	std::string newContent =
	NEWLINE_PREFIX + TYPE_PREFIX + std::to_string(T::GetStaticType()->GetId()) + ID_PREFIX +
	std::to_string(_object->GetId()) + "\n";
	return newContent;
}
