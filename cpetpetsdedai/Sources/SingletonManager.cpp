#include "../Headers/SingletonManager.h"
SingletonManager::SingletonManager() = default;

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
