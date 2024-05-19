#include "../../Headers/Scenes/EditorScene.h"
#include "../../Headers/Components/EditorComponent.h"
#include "../../Headers/Engine/GameObject.h"

EditorScene::EditorScene() : Scene("EditorScene", Scene::GetStaticType())
{
}

void EditorScene::InitializeScene(sf::RenderWindow* _window)
{
    Scene::InitializeScene(_window);
    GameObject* editor = Create<GameObject>();
    editor->Init("EditorOnly");
    auto editorComp = editor->AddComponent<EditorComponent>();
    editorComp->Init();
}

void EditorScene::UpdatePreComponent(float deltaTime)
{
}

void EditorScene::DestroyScene()
{
}

void EditorScene::OnMouseKeyDown(sf::Mouse::Button pressedKey)
{

}
