#include "Factory.h"
#include "Headers/Engine/Object.h"

Factory* Factory::GetInstance()
{
    static Factory* instance = nullptr;

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

void Factory::RegisterType(const std::string& name, const std::function<Object*()>& function, const std::function<Object*(uint64_t)>& functionWithId)
{
    if (!_objNameToCreation.contains(name))
    {
        _objNameToCreation[name] = function;
        _objNameToCreationWithId[name] = functionWithId;
    }
}

void Factory::ResetInstance()
{
    auto temp = GetInstance();
    delete temp;
    temp = nullptr;
}

void Factory::OnObjectIDChanged(uint64_t oldId, uint64_t newId)
{
    if (objectById.contains(oldId))
    {
        auto object = objectById[oldId];
        objectById.erase(oldId);
        objectById[newId] = object;
    }
}

bool Factory::CanBeCreated(const std::string& name)
{
    return _objNameToCreation.contains(name);
}

Object* Factory::CreateObjectByName(const std::string& name)
{
    if (_objNameToCreation.contains(name))
    {
        return _objNameToCreation[name]();
    }

    return nullptr;
}

Object* Factory::CreateObjectByName(const std::string& name, uint64_t id)
{
    if (_objNameToCreationWithId.contains(name))
    {
        return _objNameToCreationWithId[name](id);
    }
    return nullptr;
}


