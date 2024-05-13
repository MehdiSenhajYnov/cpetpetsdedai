#include <filesystem>
#include "../../Headers/Scenes/SceneFileEditor.h"
#include "../../Headers/Scenes/Scene.h"
#include "../../Headers/Utilities/Utilities.h"


std::string SceneFileEditor::scenePath = "Scenes/";
std::string SceneFileEditor::sceneFileExtension = ".sc";

SceneFileEditor::SceneFileEditor(): GameSystem("SceneCreator", GameSystem::GetStaticType()), level(nullptr)
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

    std::vector<std::string> sceneFileLines = FileUtilities::ReadLinesFromFile(sceneFilePath);
    

    GameObject* currentGameObject; 
    for (auto& line : sceneFileLines)
    {
        Object* currentObject;
        Type* currentType;
        if (line.starts_with("---"))
        {
            int typeStartIndex = Utilities::IndexOf(line, TYPE_PREFIX);
            int idStartIndex = Utilities::IndexOf(line, ID_PREFIX);
            if (typeStartIndex == -1 || idStartIndex == -1)
            {
                continue;
            }
            int typeEndIndex = typeStartIndex + TYPE_PREFIX.size();
            int idEndIndex = idStartIndex + ID_PREFIX.size();
            std::string typeString = line.substr(typeEndIndex, idStartIndex - typeEndIndex);
            std::string idString = line.substr(idEndIndex, line.size() - idEndIndex);
            currentType = Type::GetType(typeString);
            if (currentType == nullptr)
            {
                continue;
            }
            if (currentType->Equals(GameObject::GetStaticType()))
            {
                currentGameObject = level->CreateGameObject("temp");
                currentObject = currentGameObject;
                
            }
            else
            {
                std::cout << "Type not recognized. type name : " << typeString << std::endl;
            }
        }
        
    }
}

void SceneFileEditor::TestLoadScene(const TList<std::string>& _serialised) const
{
    std::string toFindGameObjectID = "!t!-1829605404";
    for (auto& line : _serialised)
    {
        if (line.find(toFindGameObjectID) != std::string::npos)
        {
            GameObject* currentGameObject = level->CreateGameObject("temp");
            
        }
    }
}


void SceneFileEditor::SaveScene() const
{

    TList<SerializeBuffer> buffers;
    buffers.reserve(level->GetGameObjects().size());

    std::string tempContent;
    std::string finalContent;
    
    for (int i = 0; i < level->GetGameObjects().size(); ++i)
    {
        buffers.push_back(SerializeBuffer());
     
        uint64_t objID = level->GetGameObjects()[i]->Serialize(buffers[i], tempContent);
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
