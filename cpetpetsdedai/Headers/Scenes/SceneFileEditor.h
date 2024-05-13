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
	AddType(SceneEditor, GameSystem)
	
	bool CreateNewScene() const;
	void LoadScene() const;
	void TestLoadScene(const TList<std::string>& _serialised) const;
	
	void SaveScene() const;
	
	std::string sceneName;
	std::string GetScenePath() const;

	//void CreateGameObject(GameObject* _gameObject) const;

	template <IsSerialisable T>
	void WriteObjectInFile(T* _object) const;
	template <IsSerialisable T>
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

template <IsSerialisable T>
void SceneFileEditor::WriteObjectInFile(T* _object) const
{
	if (level == nullptr)
	{
		return;
	}

	SerializeBuffer buffer;
	std::string_view temp;

	_object->Serialize(buffer, temp);
	if (!buffer.startBuffer.empty())
	{
		FileUtilities::AppenInFileAtLine(GetScenePath(), buffer.startBuffer, 0);
	}
	if (!buffer.mainBuffer.empty())
	{
		FileUtilities::AppendInFile(GetScenePath(), buffer.mainBuffer);
	}
	if (!buffer.endBuffer.empty())
	{
		FileUtilities::AppendInFile(GetScenePath(), buffer.endBuffer);
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

template <IsSerialisable T>
std::string SceneFileEditor::GetObjectSerializePrefix(T* _object)
{
	std::string newContent =
	NEWLINE_PREFIX + TYPE_PREFIX + std::to_string(T::GetStaticType()->GetId()) + ID_PREFIX + std::to_string(_object->GetId()) + "\n";
	return newContent;
}
