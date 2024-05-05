#pragma once
#include <cstdint>
#include <unordered_map>

#include "TypeInfo.h"
#include "TypeName.h"
#include "../Utilities/Utilities.h"


class TypeId
{
public:
    friend bool operator==(const TypeId& _lhs, const TypeId& _rhs)
    {
        return _lhs.id == _rhs.id;
    }

    friend bool operator!=(const TypeId& _lhs, const TypeId& _rhs)
    {
        return !(_lhs == _rhs);
    }
    TypeId() = default;
    TypeId(uint64_t _id) : id(_id) {}
    
    template <typename T>
    static TypeId Create();

    uint64_t GetId() const { return id; }
    void SetId(uint64_t _id) { id = _id; }

    const TypeInfo* GetTypeInfo() const
    {
        return GetTypeInformation(*this);
    }

    std::string GetTypeName();
    int GetTypeSize();
    int GetTypeAlignment();

    static const TypeInfo* GetTypeInformation(TypeId _typeId)
    {
        return &TypeInfos()[_typeId.GetId()];
    }

    static std::unordered_map<uint64_t, TypeInfo>& TypeInfos()
    {
        static std::unordered_map<uint64_t, TypeInfo> typeInfos;
        return typeInfos;
    }

    template <typename T>
    static void RegisterTypeId()
    {
        const auto _typeId = TypeId::Create<T>().GetId();
        if (!TypeInfos().contains(_typeId))
        {
            TypeInfos()[_typeId] = TypeInfo::Create<T>();
        }
    }

    template <typename T>
    static int GetTypeIdOf()
    { 
		return Utilities::Hash(std::string(TypeNameUtilities::TypeName<T>()));
    }
    
private:
    uint64_t id;

};

std::string TypeId::GetTypeName()
{
    return GetTypeInfo()->Name;
}

int TypeId::GetTypeSize()
{
    return GetTypeInfo()->Size;
}

int TypeId::GetTypeAlignment()
{
    return GetTypeInfo()->Alignment;
}

template <typename T>
TypeId TypeId::Create()
{
    return TypeId(GetTypeIdOf<T>());
}
