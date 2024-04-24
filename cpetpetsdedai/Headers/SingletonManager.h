#pragma once
#include "TextureManager.h"

class SingletonManager
{
public:
    SingletonManager();
    ~SingletonManager();
    void DeleteAll();
    void InitAll();
};
