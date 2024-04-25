#include "../../Headers/Scenes/Level.h"
#include "../../Headers/Engine/GameObject.h"

Level::Level() : Scene("Level", Scene::GetStaticType())
{
}

void Level::InitializeScene(sf::RenderWindow* _window)
{
    window = _window;
    
    mainCameraObject = CreateGameObject("mainCameraObject",0);
    mainCamera = Camera();
    mainCamera.Initialize(mainCameraObject, sf::Vector2f(10000, 10000), window, this);
    mainCameraObject->AddComponent(&mainCamera);
}

void Level::Update(float deltaTime)
{
    CalUpdateOnAll(deltaTime);
}

void Level::OnKeyDown(sf::Keyboard::Key pressedKey)
{
}

void Level::DestroyScene()
{
}
