#include "SingletonManager.h"

#include "../Headers/TextureManager.h"

void SingletonManager::DeleteAll()
{
    delete TextureManager::Instance();
}
