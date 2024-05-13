#pragma once
#include <map>

#include "TList.h"
#include "Headers/Utilities/AllConcepts.h"

// SINGLETON
class Object;

class Factory
{
public:
    static Factory* GetInstance();
    static void ResetInstance();

    template<typename T>
    T* CreateObject() requires IsDerivedFrom<T, Object>;

    template<typename T>
    T* CreateObject(uint64_t id) requires IsDerivedFrom<T, Object>;

    template<typename T>
    void DestroyObject(T* object) requires IsDerivedFrom<T, Object>;

    void ClearAll();
    
    TList<Object*>& GetObjects();
    std::map<uint64_t, Object*>& GetObjectById();

    ~Factory();
public:
    TList<Object*> objects;
    std::map<uint64_t, Object*> objectById;
    

private:
    Factory() = default;
};

template <typename T>
T* Factory::CreateObject() requires IsDerivedFrom<T, Object>
{
    T* newObject = new T();
    objects.push_back(newObject);
    objectById[newObject->GetId()] = newObject;
    return newObject;
}

template <typename T>
T* Factory::CreateObject(uint64_t id) requires IsDerivedFrom<T, Object>
{
    //T* newObject = new T(id);
    T* newObject;
    objects.push_back(newObject);
    objectById[newObject->GetId()] = newObject;
    return newObject;
}

template <typename T>
void Factory::DestroyObject(T* object) requires IsDerivedFrom<T, Object>
{
    
    objects.RemoveElement(object);
    if (objectById.contains(object->GetId()))
    {
        objectById.erase(object->GetId());
    }
    object->PreDestroy();
    delete object;
    object = nullptr;
}
