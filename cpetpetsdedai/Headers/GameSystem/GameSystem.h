#pragma once
#include "../Engine/Object.h"

class GameSystem : public Object
{
public:
    AddType(GameSystem, Object::GetStaticType())
    GameSystem() = default;
    GameSystem(const std::string& typeName, Type* parentType)
        : Object(typeName, parentType)
    {
    }
};
