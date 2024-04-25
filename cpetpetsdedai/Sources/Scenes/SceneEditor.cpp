#include <filesystem>
#include <fstream>
#include <ranges>
#include "../../Headers/Scenes/SceneEditor.h"

#include "../../Headers/Scenes/Level.h"
#include "../../Headers/Scenes/Scene.h"
#include "../../Headers/Utilities/FileUtilities.h"
#include "../../Headers/Utilities/Utilities.h"


std::string SceneEditor::scenePath = "Scenes/";
std::string SceneEditor::sceneFileExtension = ".sc";

SceneEditor::SceneEditor(): GameSystem("SceneCreator", GameSystem::GetStaticType())
{
}

bool SceneEditor::CreateNewScene(std::string _sceneName)
{
    std::string sceneFilePath = GetScenePath(_sceneName);
    if (FileUtilities::FileExists(sceneFilePath))
    {
        return false;
    }

    FileUtilities::CreateDirectory(scenePath);
    FileUtilities::WriteInFile(sceneFilePath, "SceneName=" + _sceneName + "\n");
    return true;
}

void SceneEditor::LoadScene(std::string _sceneName)
{
    std::string sceneFilePath = GetScenePath(_sceneName);
    if (!FileUtilities::FileExists(sceneFilePath))
    {
        return;
    }

    std::vector<std::string> sceneFileLines = FileUtilities::ReadLinesFromFile(sceneFilePath);

    Level level;
    std::shared_ptr<GameObject> currentGameObject; 
    for (auto& line : sceneFileLines)
    {
        std::vector<std::string> lineParts = Utilities::SplitString(line, "=");
        if (lineParts[0] == "SceneName")
        {
            level.sceneName = lineParts[1];
        } else if (lineParts[0] == "GameObject")
        {
            std::vector<std::string> GameObjectInfo = Utilities::SplitString(lineParts[1], ",");
            currentGameObject = level.CreateGameObject(GameObjectInfo[0], std::stoi(lineParts[1]));

            
        }
    }
    
    
}

std::string SceneEditor::GetScenePath(std::string _sceneName)
{
    return scenePath + _sceneName + sceneFileExtension;
}

SceneEditor::~SceneEditor()
{
}
