#include <filesystem>
#include "../../Headers/Scenes/SceneFileEditor.h"
#include "../../Headers/Scenes/Scene.h"
#include "../../Headers/Utilities/Utilities.h"


std::string SceneFileEditor::scenePath = "Scenes/";
std::string SceneFileEditor::sceneFileExtension = ".sc";

SceneFileEditor::SceneFileEditor(): GameSystem("SceneFileEditor", GameSystem::GetStaticType())
{
}

bool SceneFileEditor::CreateNewScene() const
{
    if (level == nullptr)
    {
        return false;
    }
    std::string sceneFilePath = GetScenePath();
    if (FileUtilities::FileExists(sceneFilePath))
    {
        return false;
    }

    FileUtilities::CreateDirectory(scenePath);
    std::string baseHeaderScene = "--- !t!header\n  sceneName: " + GetSceneName() + "\n";
    FileUtilities::WriteInFile(sceneFilePath, baseHeaderScene);
    
    return true;
}

void SceneFileEditor::LoadScene() const
{
    if (level == nullptr)
    {
        return;
    }
    std::string sceneFilePath = GetScenePath();
    if (!FileUtilities::FileExists(sceneFilePath))
    {
        return;
    }

    std::string sceneFullContent = FileUtilities::ReadFromFile(sceneFilePath);
    int endOfSceneIdIndex = Utilities::IndexOf(sceneFullContent, "\n");
    std::string sceneIdStr = sceneFullContent.substr(9, endOfSceneIdIndex - 9);
    uint64_t sceneId = std::stoull(sceneIdStr);
    level->SetId(sceneId);

    level->AddMethods();
    
    std::string sceneContent = sceneFullContent.substr(endOfSceneIdIndex + 1);
    
    auto splittedByNewElements = Utilities::SplitString(sceneContent, "--- ");
    std::string toFindGameObjectID = "!t!GameObject";

    for (auto& serializedElement : splittedByNewElements)
    {
        if (serializedElement.find(toFindGameObjectID) != std::string::npos)
        {
            int indexOfNewLine = Utilities::IndexOf(serializedElement, "\n");
            int indexOfIdDeclaration = Utilities::IndexOf(serializedElement, "!i!");
            uint64_t objID = std::stoull(serializedElement.substr(indexOfIdDeclaration + 3, indexOfNewLine - indexOfIdDeclaration - 3));
			
            std::string  serializedGameObject = serializedElement.substr(indexOfNewLine + 1);
            GameObject* gameObject = Create<GameObject>(objID);
            
            gameObject->Deserialize(serializedGameObject, sceneContent);
        }
		
    }


}

void SceneFileEditor::SaveScene() const
{

    TList<SerializeBuffer> buffers;
    buffers.reserve(level->GetGameObjects().size());

    std::string tempContent;

    std::string finalContent = "SCENEID: " + std::to_string(level->GetId()) + "\n";
    
    for (int i = 0; i < level->GetGameObjects().size(); ++i)
    {
        buffers.push_back(SerializeBuffer());
     
        level->GetGameObjects()[i]->Serialize(buffers[i], tempContent);
        tempContent += (buffers[i].startBuffer + buffers[i].mainBuffer + buffers[i].endBuffer);
        
        finalContent += buffers[i].startBuffer;
    }
    

    for (auto& buffer : buffers)
    {
        finalContent += buffer.mainBuffer;
    }
    for (auto& buffer : buffers)
    {
        finalContent += buffer.endBuffer;
    }
    
    
    FileUtilities::WriteInFile(GetScenePath(), finalContent);
}

std::string SceneFileEditor::GetScenePath() const
{
    return scenePath + GetSceneName() + sceneFileExtension;
}

void SceneFileEditor::SetCurrentScene(Scene* _scene)
{
    level = _scene;
}

Scene* SceneFileEditor::GetCurrentScene() const
{
    return level;
}

std::string SceneFileEditor::GetSceneName() const
{
    if (level == nullptr)
    {
        return "";
    }
    return level->GetType()->GetName();
}

SceneFileEditor::~SceneFileEditor() = default;
