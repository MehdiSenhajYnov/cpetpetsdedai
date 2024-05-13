#include "Factory.h"
#include "Headers/Engine/Object.h"

Factory* Factory::GetInstance()
{
    static Factory* instance;

    if (instance == nullptr)
    {
        instance = new Factory();
    }
    return instance;
}

void Factory::ClearAll()
{
    for (int i = 0; i < objects.size(); ++i)
    {
        auto objectToDelete = objects[i];
        if (objectToDelete != nullptr)
        {
            delete objectToDelete;
            objectToDelete = nullptr;
        }
    }
    
    objects.clear();
    objectById.clear();
}

TList<Object*>& Factory::GetObjects()
{
    return objects;
}

std::map<uint64_t, Object*>& Factory::GetObjectById()
{
    return objectById;
}

Factory::~Factory()
{
    // en detruisant l'objet, il peut detruire les enfants, ducoup normalement avec for i il devrait pas y avoir de problemes
    for (int i = 0; i < objects.size(); ++i)
    {
        auto objectToDelete = objects[i];
        delete objectToDelete;
        objectToDelete = nullptr;
    }

    objects.clear();
    objectById.clear();

}

void Factory::ResetInstance()
{
    auto temp = GetInstance();
    delete temp;
    temp = nullptr;
}
