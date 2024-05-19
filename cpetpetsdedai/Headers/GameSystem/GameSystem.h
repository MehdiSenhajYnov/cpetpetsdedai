#pragma once
#include "../Engine/Object.h"

class GameSystem : public Object
{
public:
    ADD_TYPE(GameSystem, Object, REG_TYPE)
    GameSystem() = default;
    GameSystem(const std::string& typeName, Type* parentType)
        : Object(typeName, parentType)
    {
    }
};
