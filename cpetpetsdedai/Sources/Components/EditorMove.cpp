#include "../../Headers/Components/EditorMove.h"

#include "../../Headers/Components/SpriteRenderer.h"

EditorMove::EditorMove() : GameObject("EditorMovable", GameObject::GetStaticType())
{
}

EditorMove::EditorMove(const std::string& _typeName, Type* parentType): GameObject(_typeName, parentType)
{
}


EditorMove::~EditorMove()
{
    GameObject::~GameObject();
}

void EditorMove::Init(std::string _name)
{
    GameObject::Init(_name);
    auto spriteRenderer = AddComponent<SpriteRenderer>();
    spriteRenderer->SetSprite("EditorMove");
}
