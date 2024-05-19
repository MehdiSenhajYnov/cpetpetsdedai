#include "EditorCameraUserMove.h"

#include "Headers/Engine/GameObject.h"
#include "Headers/Input/Input.h"

EditorCameraUserMove::EditorCameraUserMove() : Component("EditorCameraUserMove", Component::GetStaticType())
{
    componentWorkType = ComponentWorkType::PlayAndEditor;
}

void EditorCameraUserMove::Start()
{
}

void EditorCameraUserMove::Update(float deltaTime)
{

    if (Input::GetKeyDown(KeyCode::MiddleMouse))
    {
        lastMousePosition = Input::GetMousePosition();
    }
    if (Input::GetKey(KeyCode::MiddleMouse))
    {
        deltaMousePosition = Input::GetMousePosition() - lastMousePosition;
        gameObject->Move(-deltaMousePosition);
        lastMousePosition = Input::GetMousePosition();
    }
    
}
