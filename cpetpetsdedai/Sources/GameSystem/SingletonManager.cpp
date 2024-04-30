#include "../../Headers/GameSystem/SingletonManager.h"

#include "../../CameraManager.h"
#include "../../RendererManager.h"
#include "../../Headers/GameSystem/TextureManager.h"

SingletonManager::SingletonManager() = default;

SingletonManager::~SingletonManager()
{
    DeleteAll();
}

void SingletonManager::DeleteAll()
{
    TextureManager::ResetInstance();
    CameraManager::ResetInstance();
    RendererManager::ResetInstance();
}

void SingletonManager::InitAll()
{
    TextureManager::Instance()->Init();
}
