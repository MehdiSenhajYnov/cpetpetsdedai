#include "../../Headers/GameSystem/SingletonManager.h"
#include "../../Headers/GameSystem/TextureManager.h"

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
