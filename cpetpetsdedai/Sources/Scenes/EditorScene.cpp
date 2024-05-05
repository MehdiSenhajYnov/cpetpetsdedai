#include <ranges>
#include "../../Headers/Scenes/EditorScene.h"

#include "../../RoundedRectangle.h"
#include "../../Headers/Components/Animator.h"
#include "../../Headers/Engine/GameObject.h"
#include "../../Headers/Utilities/Utilities.h"
#include "../../Headers/Components/SpriteRenderer.h"
#include "../../Headers/Components/Camera.h"


EditorScene::EditorScene() : Scene("EditorScene", Scene::GetStaticType()),
editorMove(nullptr), contextMenu(nullptr)
{
}

void EditorScene::InitializeScene(sf::RenderWindow* _window)
{
    Scene::InitializeScene(_window);
    
    editorMove = CreateGameObjectImmediate("EditorMove");
    SpriteRenderer* editorMoveSpriteRenderer = editorMove->AddComponent<SpriteRenderer>();
    editorMoveSpriteRenderer->SetSprite("EditorMove");
    editorMoveSpriteRenderer->SetScale(sf::Vector2f(0.1f,0.1f));
    editorMoveSpriteRenderer->SetColor(sf::Color::Green);
    editorMoveSpriteRenderer->SetZIndex(2);
    editorMove->SetPosition(100, 200);
    editorMove->SetIsActive(false);


    auto tempObj = CreateGameObjectImmediate("temp");
    SpriteRenderer* tempSpriteRenderer = tempObj->AddComponent<SpriteRenderer>();
    tempSpriteRenderer->SetSprite("Square");
    tempSpriteRenderer->SetColor(sf::Color::Red);
    tempObj->SetPosition(100, 100);
    
    contextMenu = CreateGameObjectImmediate<ContextMenu>("ContextMenu");
    contextMenu->Init("ContextMenu");
    contextMenu->AddToContextMenu("Create Game Object", &EditorScene::CreateGameObjectContextMenu, this);
    contextMenu->AddToContextMenu("Exit", &EditorScene::CreateGameObjectContextMenu, this);
    contextMenu->AddToContextMenu("TEST LONG TEXT TEST LONG TEXT TEST LONG TEXT", &EditorScene::CreateGameObjectContextMenu, this);
    contextMenu->SetIsActive(false);


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
        if (!contextMenu->IsInsideContextMenu(mousePositionWorld))
        {
            DisableContextMenu();
        }
    }
}

void EditorScene::CreateGameObjectContextMenu(Button* btn)
{
    std::cout << btn->GetTextComponent()->GetString() << " clicked" << std::endl;
    auto createdObject = CreateGameObject("CreatedObject");
    SpriteRenderer* createdObjectSpriteRenderer = createdObject->AddComponent<SpriteRenderer>();
    createdObjectSpriteRenderer->SetSprite("Square");
    createdObjectSpriteRenderer->SetColor(sf::Color::Blue);
    createdObject->SetPosition(mousePositionWorld);
    DisableContextMenu();
}

void EditorScene::CreateContextMenu()
{
    // context menu origin is at center of first button
    float halfWidth = contextMenu->GetWidth()/2;
    float halfOneHeight = contextMenu->GetHeight()/2;
    float fullHeight = contextMenu->GetFullHeight();
    sf::Vector2f newPostion = {mousePosition.x + halfWidth, mousePosition.y + halfOneHeight};

    if (newPostion.x + halfWidth > window->getViewport(window->getView()).left + window->getViewport(window->getView()).width)
    {
        newPostion.x = mousePosition.x - halfWidth;
    }
    if (newPostion.y + (fullHeight - halfOneHeight)> window->getViewport(window->getView()).top + window->getViewport(window->getView()).height)
    {
        newPostion.y = mousePosition.y - fullHeight + halfOneHeight;
    }

    contextMenu->SetPosition(newPostion);

    contextMenu->SetIsActive(true);
    
    // contextMenuBackground = CreateGameObjectImmediate("ContextMenuBackground");
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
    contextMenu->SetIsActive(false);
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

        if (_gameObject == contextMenu)
        {
            continue;
        }
        
        for (auto drawableLayer : *(_gameObject->GetDrawableComponents()))
        {
            for (auto& _spriterenderer : drawableLayer.drawableComponents)
            {
                if (Utilities::IsInBounds(mousePositionWorld, _spriterenderer->GetAttachedObject()->GetPosition(), _spriterenderer->GetOriginalSize()))
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
