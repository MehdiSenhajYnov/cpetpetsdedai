#pragma once
#include "../Engine/GameObject.h"

class EditorMove : public GameObject
{
public:
    EditorMove();
    EditorMove(const std::string& _typeName, Type* parentType);
    AddType(EditorMovable, GameObject::GetStaticType())

    ~EditorMove() override;
    void Init(std::string _name) override;

protected:
};
