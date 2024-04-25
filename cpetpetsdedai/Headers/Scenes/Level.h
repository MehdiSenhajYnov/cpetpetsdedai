#pragma once
#include "Scene.h"
#include "../Components/Camera.h"

class Level : public Scene
{
public:
    Level();
    AddType(Level, Scene::GetStaticType())
    
    void InitializeScene(sf::RenderWindow* _window) override;
    void Update(float deltaTime) override;
    void OnKeyDown(sf::Keyboard::Key pressedKey) override;
    void DestroyScene() override;


    std::shared_ptr<GameObject> mainCameraObject;
    Camera mainCamera;
};



