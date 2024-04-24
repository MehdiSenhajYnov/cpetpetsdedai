#pragma once
#include <filesystem>
#include <fstream>
#include "../Headers/SceneEditor.h"
#include "../Headers/FileUtilities.h"


std::string SceneEditor::scenePath = "Scenes/";
std::string SceneEditor::sceneFileExtension = ".sc";

SceneEditor::SceneEditor(): GameSystem("SceneCreator", Object::ObjectType())
{
}

bool SceneEditor::CreateScene(std::string _sceneName)
{
    std::string sceneFilePath = scenePath + _sceneName + sceneFileExtension;
    if (FileUtilities::FileExists(sceneFilePath))
    {
        return false;
    }

    FileUtilities::CreateDirectory(scenePath);
    FileUtilities::WriteInFile(sceneFilePath, "SceneName=" + _sceneName + "\n");
    return true;
}

SceneEditor::~SceneEditor()
{
}
