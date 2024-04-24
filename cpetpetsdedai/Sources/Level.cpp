#include "../Headers/Level.h"

void Level::InitializeScene(sf::RenderWindow* _window)
{
    window = _window;
    
    mainCameraObject = CreateGameObject("mainCameraObject",0);
    mainCamera = Camera();
    mainCamera.Initialize(mainCameraObject, sf::Vector2f(10000, 10000), window, this);
    AddComponent(mainCameraObject, &mainCamera);
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
