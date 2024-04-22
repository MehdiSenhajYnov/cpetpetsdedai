#include "SingletonManager.h"

#include "../Headers/TextureManager.h"

SingletonManager::SingletonManager()
{
}

SingletonManager::~SingletonManager()
{
    DeleteAll();
}



void SingletonManager::DeleteAll()
{
    TextureManager::ResetInstance();
}

void SingletonManager::InitAll()
{
    TextureManager::Instance()->Init();
}
