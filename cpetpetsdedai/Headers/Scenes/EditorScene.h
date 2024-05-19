#pragma once
#include "Scene.h"
#include "../../ContextMenu.h"

class EditorScene : public Scene
{
public:
    EditorScene();
    ADD_TYPE(EditorScene, Scene, REG_TYPE)
    
    void InitializeScene(sf::RenderWindow* _window) override;
    void UpdatePreComponent(float deltaTime) override;
    void DestroyScene() override;
    void OnMouseKeyDown(sf::Mouse::Button pressedKey) override;
};



