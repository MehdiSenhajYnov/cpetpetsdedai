#pragma once
#include "Scene.h"
#include "Camera.h"
#include "GraphicDebugger.h"
#include "SceneManager.h"
#include "GameScene.h"


class Level : public Scene
{
public:
    Level() = default;
    void InitializeScene(sf::RenderWindow* _window) override;
    void Update(float deltaTime) override;
    void OnKeyDown(sf::Keyboard::Key pressedKey) override;
    void DestroyScene() override;


    std::shared_ptr<GameObject> mainCameraObject;
    Camera mainCamera;
};



