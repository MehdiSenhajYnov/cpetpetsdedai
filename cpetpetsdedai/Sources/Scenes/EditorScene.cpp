#include <ranges>
#include "../../Headers/Scenes/EditorScene.h"
#include "../../Headers/Engine/GameObject.h"
#include "../../Headers/Utilities/Utilities.h"
#include "../../Headers/Components/SpriteRenderer.h"
#include "../../Headers/Components/Camera.h"


EditorScene::EditorScene() : Scene("Level", Scene::GetStaticType())
{
}

void EditorScene::InitializeScene(sf::RenderWindow* _window)
{
    window = _window;
    
    mainCameraObject = CreateGameObject("mainCameraObject",0);
    
    mainCamera = mainCameraObject->AddComponent<Camera>(sf::Vector2f(10000, 10000), window, this);
    
}

void EditorScene::Update(float deltaTime)
{

    
    
    CalUpdateOnAll(deltaTime);
}

void EditorScene::OnKeyDown(sf::Keyboard::Key pressedKey)
{
}

void EditorScene::DestroyScene()
{
}

void EditorScene::EditorUpdate(float deltaTime)
{
    mousePosition = sf::Vector2f(sf::Mouse::getPosition(*mainCamera->GetCurrentWindow()));
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if (!isMousePressed)
        {
            isMousePressed = true;
    
            // TODO : reverse loop sur GetSpriteRenderersByZIndex, et checker si je touche un sprite renderer, si c'est le cas afficher le move
            for(auto& [zIndex, spriteRenderers] :  std::ranges::views::reverse(*GetSpriteRenderersByZIndex())) {
                for (auto _spriterenderer : spriteRenderers)
                {
                    if (Utilities::IsInBounds(mousePosition, _spriterenderer->GetAttachedObject()->GetPosition(), _spriterenderer->GetSize()))
                    {
                        
                    }

                }
            }
            
        }
    }
    else
    {
        if (isMousePressed)
        {
            isMousePressed = false;
    
        }
    }

}
