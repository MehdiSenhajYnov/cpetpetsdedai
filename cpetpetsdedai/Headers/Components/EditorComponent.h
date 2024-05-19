#pragma once
#include "Component.h"


class Button;
class ContextMenu;
class SpriteRenderer;
class Scene;

class EditorComponent : public Component
{
public:
    ADD_TYPE(EditorComponent, Component, REG_TYPE)
    EditorComponent();
    void Start() override;
    void Update(float deltaTime) override;

    void CreateGameObjectContextMenu(Button* _btn);
    void DisableContextMenu() const;

    void CheckMouseSelection();
    void CreateContextMenu() const;
    void LateUpdate(float deltaTime) override;

private:
    GameObject*  editorMove = nullptr;
    GameObject* selectedObject = nullptr;
    sf::Vector2f selectedObjectOffset = sf::Vector2f(0, 0);
    ContextMenu* contextMenu = nullptr;

    sf::Vector2f mousePosition = sf::Vector2f(0, 0);
    sf::Vector2f mousePositionWorld = sf::Vector2f(0, 0);

    bool isDragging = false;
    std::string UsedSelectionSystemName = "INSPECTOR";
};
