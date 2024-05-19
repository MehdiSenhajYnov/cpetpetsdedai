#pragma once
#include <map>
#include <string>

class Type;

class TypeContainer
{
public:

    static void AddType(Type* type, std::string name, int id)
    {
        GetAllTypes()[name] = type;
        GetAllTypesById()[id] = type;
    }
    
    static std::map<std::string, Type*>& GetAllTypes()
    {
        static std::map<std::string, Type*> allTypes;
        return allTypes;
    }
    
    static std::map<int, Type*>& GetAllTypesById()
    {
        static std::map<int, Type*> allTypesById;
        return allTypesById;
    }

};
