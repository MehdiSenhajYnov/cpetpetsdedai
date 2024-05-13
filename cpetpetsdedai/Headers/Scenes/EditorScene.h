#pragma once
#include "Scene.h"
#include "../../ContextMenu.h"

class EditorScene : public Scene
{
public:
    EditorScene();
    AddType(Level, Scene)
    
    void InitializeScene(sf::RenderWindow* _window) override;
    void UpdatePreComponent(float deltaTime) override;
    void DestroyScene() override;
    void OnMouseKeyDown(sf::Mouse::Button pressedKey) override;


    void CreateGameObjectContextMenu(Button* _btn);
    void CreateContextMenu() const;
    void DisableContextMenu() const;
protected:
    sf::Vector2f mousePosition = sf::Vector2f(0, 0);
    sf::Vector2f mousePositionWorld = sf::Vector2f(0, 0);
    
    void EditorUpdate(float deltaTime);
    void CheckMouseSelection();

    bool isMousePressed = false;

private:
    GameObject* editorMove = nullptr;
    GameObject* selectedObject = nullptr;
    SpriteRenderer* selectedSpriteRenderer = nullptr;
    sf::Vector2f selectedObjectOffset = sf::Vector2f(0, 0);
    ContextMenu* contextMenu = nullptr;

    //GameObject* contextMenuBackground;
    //SpriteRenderer* contextMenuBackgroundSpriteRenderer;

};



