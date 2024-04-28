#pragma once
#include "Scene.h"

class EditorScene : public Scene
{
public:
    EditorScene();
    AddType(Level, Scene::GetStaticType())
    
    void InitializeScene(sf::RenderWindow* _window) override;
    void Update(float deltaTime) override;
    void OnKeyDown(sf::Keyboard::Key pressedKey) override;
    void DestroyScene() override;


    std::shared_ptr<GameObject> mainCameraObject;
    Camera* mainCamera;

protected:
    sf::Vector2f mousePosition;
    void EditorUpdate(float deltaTime);
    bool isMousePressed = false;
};



