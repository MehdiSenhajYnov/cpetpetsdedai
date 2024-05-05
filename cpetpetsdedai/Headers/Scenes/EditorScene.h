#pragma once
#include "Scene.h"
#include "../../ContextMenu.h"

class EditorScene : public Scene
{
public:
    EditorScene();
    AddType(Level, Scene::GetStaticType())
    
    void InitializeScene(sf::RenderWindow* _window) override;
    void Update(float deltaTime) override;
    void DestroyScene() override;
    void OnMouseKeyDown(sf::Mouse::Button pressedKey) override;


    void CreateGameObjectContextMenu(Button* btn);
    void CreateContextMenu();
    void DisableContextMenu();
protected:
    sf::Vector2f mousePosition;
    sf::Vector2f mousePositionWorld;
    
    void EditorUpdate(float deltaTime);
    void CheckMouseSelection();

    bool isMousePressed = false;

private:
    GameObject* editorMove;
    
    GameObject* selectedObject = nullptr;
    sf::Vector2f selectedObjectOffset;

    //GameObject* contextMenuBackground;
    //SpriteRenderer* contextMenuBackgroundSpriteRenderer;

    ContextMenu* contextMenu;
};



