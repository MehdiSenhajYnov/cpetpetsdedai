#pragma once
#include <map>
#include <string>
#include <vector>
#include "TList.h"
#include "Headers/Engine/Field.h"
template<typename T>
concept isField =
    std::is_base_of_v<BaseField*, T> &&
    std::is_convertible_v<const volatile T*, const volatile BaseField*>;

class Type {
public:
    Type() = default;
    Type(const std::string& name, Type* parent);
    Type(const std::string& name, Type* parent, TList<BaseField*> fields);
    ~Type();
    
    int GetId() const;
    std::string GetName();
    Type* GetParent() const;
    bool Equals(const Type& Other) const;
    bool Equals(const Type* _other) const;

    TList<BaseField*>& GetAllFields();

    template <CanString T>
    void CreateField(std::string fieldName);

    
    template <CanString T>
    void CreateField(std::string fieldName, std::function<void(T)>);

    template <CanString T>
    void CreateField(std::string fieldName, T value);
    
    
    static int typeCount;
    
    static Type* GetType(const std::string& name);
    static std::vector<Type*> GetAllChildren(const Type& parent);
    static bool IsOrIsDescendantOf(const Type* toCheck, const Type* parent);
    
    static std::map<std::string, Type*>& GetAllTypes();
    static std::map<int, Type*>& GetAllTypesById();
    
private:
    int id;
    std::string name;
    Type *parent = nullptr;
    TList<BaseField*> allFields;

};


template <CanString T>
void Type::CreateField(std::string fieldName)
{
    Field<T>* field = new Field<T>(fieldName);
    GetAllFields().push_back(field);
}

template <CanString T>
void Type::CreateField(std::string fieldName, std::function<void(T)>)
{
    this->CreateField<T>(fieldName);
}

template <CanString T>
void Type::CreateField(std::string fieldName, T value)
{
    Field<T>* field = new Field<T>(fieldName, value);
    GetAllFields().push_back(field);
}

