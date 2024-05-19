#include <ranges>
#include "EditorComponent.h"
#include "../Scenes/Scene.h"
#include "SpriteRenderer.h"
#include "../../CameraManager.h"
#include "../../ContextMenu.h"
#include "../Input/Input.h"
#include "Camera.h"
#include "../../EngineUI.h"
#include "../../RendererManager.h"
#include "../EngineUI/SelectionSystem.h"
#include "../Scenes/SceneManager.h"

EditorComponent::EditorComponent() : Component("EditorComponent", Component::GetStaticType())
{
    
}

void EditorComponent::Start()
{
    editorMove = Create<GameObject>();
    editorMove->SetCanBeSerialized(false);
    editorMove->Init("EditorMove");
    SpriteRenderer* editorMoveSpriteRenderer = editorMove->AddComponent<SpriteRenderer>();
    editorMoveSpriteRenderer->SetSprite("EditorMove");
    editorMoveSpriteRenderer->SetScale(sf::Vector2f(0.1f,0.1f));
    editorMoveSpriteRenderer->SetColor(sf::Color::Green);
    editorMoveSpriteRenderer->SetZIndex(2);
    editorMove->SetPosition(100, 200);
    editorMove->SetIsActive(false);

    contextMenu = Create<ContextMenu>();
    contextMenu->SetCanBeSerialized(false);
    contextMenu->Init("ContextMenu");
    contextMenu->AddToContextMenu("Create Game Object", &EditorComponent::CreateGameObjectContextMenu, this);
    contextMenu->AddToContextMenu("Exit", &EditorComponent::CreateGameObjectContextMenu, this);
    contextMenu->AddToContextMenu("TEST LONG TEXT TEST LONG TEXT TEST LONG TEXT", &EditorComponent::CreateGameObjectContextMenu, this);
    contextMenu->SetIsActive(false);


}

void EditorComponent::Update(float deltaTime)
{
   
    
    // if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    // {
    //     if (!isMousePressed)
    //     {
    //         isMousePressed = true;
    //         CheckMouseSelection();
    //     }
    // }
    // else
    // {
    //     if (isMousePressed)
    //     {
    //         isMousePressed = false;
    //         selectedObject = nullptr;
    //     }
    // }
    //
    // if (isMousePressed && selectedObject != nullptr)
    // {
    //     selectedObject->SetPosition(mousePositionWorld + selectedObjectOffset);
    //     editorMove->SetPosition(selectedObject->GetPosition());
    // }
}

void EditorComponent::CreateGameObjectContextMenu(Button* _btn)
{
    std::cout << _btn->GetTextComponent()->GetString() << " clicked" << std::endl;
    auto createdObject = Create<GameObject>();
    createdObject->Init("CreatedObject" + std::to_string(createdObject->GetId()));
    SpriteRenderer* createdObjectSpriteRenderer = createdObject->AddComponent<SpriteRenderer>();
    createdObjectSpriteRenderer->SetSprite("Square");
    createdObjectSpriteRenderer->SetColor(sf::Color::Blue);
    createdObject->SetPosition(mousePositionWorld);
    DisableContextMenu();
}

void EditorComponent::DisableContextMenu() const
{
    contextMenu->SetIsActive(false);
}
void EditorComponent::CheckMouseSelection()
{
    for (const auto& drawableLayer : RendererManager::GetInstance()->GetDrawableLayers() | std::views::reverse)
    {
        for (const auto& drawableComponent : drawableLayer.drawableComponents | std::views::reverse)
        {
            if (drawableComponent->GetAttachedObject() == editorMove)
            {
                continue;
            }
            if (drawableComponent->GetAttachedObject() == contextMenu)
            {
                continue;
            }
            const sf::Vector2f drawableSize = drawableComponent->GetCurrentSize();
            const sf::Vector2f _goScale = drawableComponent->GetAttachedObject()->GetScale();
            const sf::Vector2f globalScale = {drawableSize.x * _goScale.x, drawableSize.y * _goScale.y};
            if (Utilities::IsInBounds(mousePositionWorld, drawableComponent->GetAttachedObject()->GetPosition(),globalScale, Center))
            {
                selectedObject = drawableComponent->GetAttachedObject();
                SelectionSystem::SetSelectedObject(selectedObject, UsedSelectionSystemName);
                selectedObjectOffset = selectedObject->GetPosition() - mousePositionWorld;
                editorMove->SetIsActive(true);
                return;
            }
        }
    }

    selectedObject = nullptr;
    editorMove->SetIsActive(false);
}

void EditorComponent::CreateContextMenu() const
{
    // context menu origin is at center of first button
    float halfWidth = contextMenu->GetWidth()/2;
    float halfOneHeight = contextMenu->GetHeight()/2;
    float fullHeight = contextMenu->GetFullHeight();
    sf::Vector2f newPostion = {mousePosition.x + halfWidth, mousePosition.y + halfOneHeight};

    auto currentScene = SceneManager::GetInstance()->GetCurrentScene();
    auto sceneView = currentScene->GetWindow()->getView();
    auto viewPort = currentScene->GetWindow()->getViewport(sceneView);
    
    if (newPostion.x + halfWidth > (float)viewPort.left + (float)viewPort.width)
    {
        newPostion.x = mousePosition.x - halfWidth;
    }
    if (newPostion.y + (fullHeight - halfOneHeight)> (float)viewPort.top + (float)viewPort.height)
    {
        newPostion.y = mousePosition.y - fullHeight + halfOneHeight;
    }

    contextMenu->SetPosition(newPostion);

    contextMenu->SetIsActive(true);
    
}

void EditorComponent::LateUpdate(float deltaTime)
{
    if (CameraManager::GetInstance()->GetMainCamera() == nullptr || CameraManager::GetInstance()->GetMainCamera()->GetAttachedObject() == nullptr)
    {
        return;
    }
    mousePosition = Input::GetMousePosition();
    mousePositionWorld = CameraManager::GetInstance()->GetMainCamera()->GetAttachedObject()->GetPosition() + mousePosition;

    if (Input::GetKeyDown(KeyCode::LeftMouse))
    {
        selectedObject = nullptr;
        CheckMouseSelection();
        if (!contextMenu->IsInsideContextMenu(mousePositionWorld))
        {
            DisableContextMenu();
        }
    }
    if (Input::GetKeyDown(KeyCode::RightMouse))
    {
        CreateContextMenu();
    }

    if (selectedObject != nullptr)
    {
        editorMove->SetPosition(selectedObject->GetPosition());

        if (Input::GetKey(KeyCode::LeftMouse))
        {
            selectedObject->SetPosition(mousePositionWorld + selectedObjectOffset);
            editorMove->SetPosition(selectedObject->GetPosition());
        }
    }
    
}
