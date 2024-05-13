#pragma once
#include "../Engine/Object.h"

class GameSystem : public Object
{
public:
    AddType(GameSystem, Object)
    GameSystem() = default;
    GameSystem(const std::string& typeName, Type* parentType)
        : Object(typeName, parentType)
    {
    }
};
