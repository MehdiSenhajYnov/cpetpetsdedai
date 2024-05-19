#pragma once
#include "../Engine/GameObject.h"

class EditorMove : public GameObject
{
public:
    EditorMove();
    EditorMove(const std::string& _typeName, Type* parentType);
    ADD_TYPE(EditorMove, GameObject, REG_TYPE)

    ~EditorMove() override;
    void Init(const std::string& _name) override;

protected:
};
