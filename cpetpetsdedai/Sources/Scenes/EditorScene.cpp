#include <ranges>
#include "../../Headers/Scenes/EditorScene.h"

#include "../../RoundedRectangle.h"
#include "../../Headers/Engine/GameObject.h"
#include "../../Headers/Utilities/Utilities.h"
#include "../../Headers/Components/SpriteRenderer.h"
#include "../../Headers/Components/Camera.h"


EditorScene::EditorScene() : Scene("EditorScene", Scene::GetStaticType()),
editorMove(nullptr), contextMenu()
{
    contextMenu = ContextMenu();
}

void EditorScene::InitializeScene(sf::RenderWindow* _window)
{
    Scene::InitializeScene(_window);
    
    editorMove = CreateGameObject("EditorMove");
    SpriteRenderer* editorMoveSpriteRenderer = editorMove->AddComponent<SpriteRenderer>();
    editorMoveSpriteRenderer->SetSprite("EditorMove");
    editorMoveSpriteRenderer->SetScale(sf::Vector2f(0.1f,0.1f));
    editorMoveSpriteRenderer->SetColor(sf::Color::Green);
    editorMoveSpriteRenderer->SetZIndex(2);
    editorMove->SetPosition(100, 200);
    editorMove->SetIsActive(false);

    contextMenu.Init("ContextMenu");
    contextMenu.AddToContextMenu("Create Game Object", &EditorScene::CreateGameObjectContextMenu, this);
}

void EditorScene::Update(float deltaTime)
{
    CalUpdateOnAll(deltaTime);
    EditorUpdate(deltaTime);
}

void EditorScene::DestroyScene()
{
}

void EditorScene::OnMouseKeyDown(sf::Mouse::Button pressedKey)
{
    if (pressedKey == sf::Mouse::Right)
    {
        CreateContextMenu();
    } else if (pressedKey == sf::Mouse::Left)
    {
        if (!contextMenu.IsInBounds(mousePositionWorld))
        {
            DisableContextMenu();
        }
    }
}

void EditorScene::CreateGameObjectContextMenu(Button* btn)
{
    std::cout << "Create Game Object" << std::endl;
}

void EditorScene::CreateContextMenu()
{

    contextMenu.SetPosition(mousePosition);
    contextMenu.SetIsActive(true);
    
    // contextMenuBackground = CreateGameObject("ContextMenuBackground");
    // contextMenuBackgroundSpriteRenderer = contextMenuBackground->AddComponent<SpriteRenderer>();
    // contextMenuBackgroundSpriteRenderer->SetSprite("Square");
    // contextMenuBackgroundSpriteRenderer->SetColor(sf::Color(200,200,200));
    // contextMenuBackgroundSpriteRenderer->SetZIndex(100);
    // contextMenuBackground->positionType = PositionType::UI;
    // contextMenuBackground->SetPosition(mousePosition);
    // contextMenuBackground->SetScale(1, 0.3f);
}

void EditorScene::DisableContextMenu()
{
    contextMenu.SetIsActive(false);
}


void EditorScene::EditorUpdate(float deltaTime)
{
    if (mainCamera == nullptr)
    {
        std::cout << "mainCamera is nullptr" << '\n';
        return;
    }
    mousePosition = sf::Vector2f(sf::Mouse::getPosition(*(mainCamera->GetCurrentWindow())));
    mousePositionWorld = mainCamera->GetAttachedObject()->GetPosition() + mousePosition;
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (!isMousePressed)
        {
            isMousePressed = true;
            CheckMouseSelection();
        }
    }
    else
    {
        if (isMousePressed)
        {
            isMousePressed = false;
            selectedObject = nullptr;
        }
    }
    
    if (isMousePressed && selectedObject != nullptr)
    {
        selectedObject->SetPosition(mousePositionWorld + selectedObjectOffset);
        editorMove->SetPosition(selectedObject->GetPosition());
    }
}

void EditorScene::CheckMouseSelection()
{
    for(auto& _gameObject : gameObjects) {
        if (_gameObject == editorMove)
        {
            continue;
        }

        if (_gameObject == &contextMenu)
        {
            continue;
        }
        
        for (auto drawableLayer : *(_gameObject->GetDrawableComponents()))
        {
            for (auto& _spriterenderer : drawableLayer.drawableComponents)
            {
                if (Utilities::IsInBounds(mousePositionWorld, _spriterenderer->GetAttachedObject()->GetPosition(), _spriterenderer->GetSize()))
                {
                    selectedObject = _spriterenderer->GetAttachedObject();
                    selectedObjectOffset = selectedObject->GetPosition() - mousePositionWorld;
                    editorMove->SetIsActive(true);
                    editorMove->SetPosition(selectedObject->GetPosition());
                    return;
                }
            }
        }
    }

}
