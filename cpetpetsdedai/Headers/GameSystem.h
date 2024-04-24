#pragma once
#include "Object.h"

class GameSystem : public Object
{
public:
    GameSystem() = default;
    GameSystem(const std::string& typeName, Type* parentType)
        : Object(typeName, parentType)
    {
    }
};
