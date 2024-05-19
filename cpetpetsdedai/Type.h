#pragma once
#include <map>
#include <string>
#include <vector>
#include "TList.h"
#include "Headers/Engine/Field.h"


class Type {
public:
    Type() = default;
    Type(const std::string& name, Type* parent);
    Type(const std::string& name, Type* parent, TList<BaseField*> fields);
    ~Type();

    void FreeMemory();
    
    int GetId() const;
    std::string GetName();
    Type* GetParent() const;
    bool Equals(const Type& Other) const;
    bool Equals(const Type* _other) const;
    static bool Equals(const Type* _other, const Type* _other2);

    TList<BaseField*>& GetAllFields();

    template <typename  T>
    void CreateField(std::string fieldName);
    
    template <typename T>
    void CreateField(std::string fieldName, std::function<void(T)> setter, std::function<T()> getter);

    // le C c'est pour Custom
    template<typename T,typename Class>
    void CreateFieldCSet(std::string fieldName, void(Class::* setter)(T), Class* instance, std::function<T()> getter);

    template <typename T, typename Class>
    void CreateFieldCGet(std::string fieldName, std::function<void(T)> setter, T(Class::* getter)(), Class* instance);

    template <typename T, typename Class>
    void CreateFieldC(std::string fieldName, void(Class::* setter)(T), T(Class::* getter)(), Class* instance);
    
    static int typeCount;
    
    static Type* GetType(const std::string& name);
    static std::vector<Type*> GetAllChildren(const Type* parent);
    static std::vector<Type*> GetAllChildrenRecursive(const Type* parent);
    
    static bool IsOrIsDescendantOf(const Type* toCheck, const Type* parent);
    
private:
    int id;
    std::string name;
    Type *parent = nullptr;
    TList<BaseField*> allFields;

};


template <typename  T>
void Type::CreateField(std::string fieldName)
{
    Field<T>* field = new Field<T>(fieldName);
    GetAllFields().push_back(field);
}

template <typename  T>
void Type::CreateField(std::string fieldName, std::function<void(T)> setter, std::function<T()> getter)
{
    Field<T>* field = new Field<T>(fieldName, getter, setter);
    GetAllFields().push_back(field);
}

template <typename T, typename Class>
void Type::CreateFieldCSet(std::string fieldName, void(Class::* setter)(T), Class* instance, std::function<T()> getter)
{
    std::function<void(T)> lambdaSetter = [instance, setter](T value) { (instance->*setter)(value); };
    CreateField(fieldName, lambdaSetter, getter);
}

template <typename T, typename Class>
void Type::CreateFieldCGet(std::string fieldName, std::function<void(T)> setter, T(Class::* getter)(), Class* instance)
{
    std::function<T()> lambdaGetter = [instance, getter]() { return (instance->*getter)(); };
    CreateField(fieldName, setter, lambdaGetter);
}

template <typename T, typename Class>
void Type::CreateFieldC(std::string fieldName, void(Class::* setter)(T), T(Class::* getter)(), Class* instance)
{
    std::function<void(T)> lambdaSetter = [instance, setter](T value) { (instance->*setter)(value); };
    std::function<T()> lambdaGetter = [instance, getter]() { return (instance->*getter)(); };
    CreateField(fieldName, lambdaSetter, lambdaGetter);
}

