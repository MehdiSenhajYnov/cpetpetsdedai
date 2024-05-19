#pragma once
#include <map>

#include "TList.h"
#include "Headers/Utilities/AllConcepts.h"
#include "Headers/Utilities/Event.h"

// SINGLETON
class Object;

class Factory
{
public:
    static Factory* GetInstance();
    static void ResetInstance();

    template<typename T>
    T* CreateObject() requires IsDerivedFrom<T, Object> && CanBeCreatedInFactory<T>;

    template<HasId T>
    T* CreateObject(uint64_t id) requires IsDerivedFrom<T, Object> && CanBeCreatedInFactory<T>;

    void OnObjectIDChanged(uint64_t oldId, uint64_t newId);

    bool CanBeCreated(const std::string& name);
    
    Object* CreateObjectByName(const std::string& name);
    Object* CreateObjectByName(const std::string& name, uint64_t id);

    Event<Object*> OnGameObjectCreated;
    
    template<typename T>
    void DestroyObject(T* object) requires IsDerivedFrom<T, Object>;

    void ClearAll();
    
    TList<Object*>& GetObjects();
    std::map<uint64_t, Object*>& GetObjectById();

    ~Factory();
    void RegisterType(const std::string& name, const std::function<Object*()>& function, const std::function<Object*(uint64_t)>&
                      functionWithId);

public:
    TList<Object*> objects;
    std::map<uint64_t, Object*> objectById;
    

private:
    Factory() = default;
    std::map<std::string, std::function<Object*()>> _objNameToCreation;
    std::map<std::string, std::function<Object*(uint64_t)>> _objNameToCreationWithId;

};



template <typename T>
T* Factory::CreateObject() requires IsDerivedFrom<T, Object> && CanBeCreatedInFactory<T>
{
    T* newObject = new T();
    objects.push_back(newObject);
    objectById[newObject->GetId()] = newObject;
    newObject->OnIdChanged().Subscribe(&Factory::OnObjectIDChanged, this);
    OnGameObjectCreated.InvokeEvent(newObject);
    return newObject;
}

template <HasId T>
T* Factory::CreateObject(uint64_t id) requires IsDerivedFrom<T, Object> && CanBeCreatedInFactory<T> 
{
    T* newObject = new T();
    newObject->SetId(id);
    objects.push_back(newObject);
    objectById[newObject->GetId()] = newObject;
    newObject->OnIdChanged().Subscribe(&Factory::OnObjectIDChanged, this);
    OnGameObjectCreated.InvokeEvent(newObject);
    return newObject;
}

template <typename T>
void Factory::DestroyObject(T* object) requires IsDerivedFrom<T, Object>
{
    
    objects.RemoveElement(object);
    if (object != nullptr)
    {
        if (objectById.contains(object->GetId()))
        {
            objectById.erase(object->GetId());
        }
        object->PreDestroy();
    }
    delete object;
    object = nullptr;
}
