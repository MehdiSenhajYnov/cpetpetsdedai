#include "Type.h"

int Type::typeCount = 0;

Type::Type(const std::string& name, Type* parent): name(name), parent(parent)
{
    id = std::hash<std::string>{}(name);
    if (!GetAllTypes().contains(name))
    {
        GetAllTypes()[name] = this;
        ++typeCount;
    }
    if (!GetAllTypesById().contains(id))
    {
        GetAllTypesById()[id] = this;
    }
}

Type::Type(const std::string& name, Type* parent, TList<BaseField*> fields) : id(0), name(name), parent(parent)
{
    for (auto& field : fields)
    {
        //AddField(field);
    }
}

Type::~Type()
{
    for (auto& toDelete : GetAllFields())
    {
        delete toDelete;
        toDelete = nullptr;
    }
    GetAllTypes().clear();
}

int Type::GetId() const
{
    return id;
}

std::string Type::GetName()
{
    return name;
}

Type* Type::GetParent() const
{
    return parent;
}

bool Type::Equals(const Type& Other) const
{
    return name == Other.name && (parent == nullptr || parent == Other.parent);
}

bool Type::Equals(const Type* _other) const
{
    return name == _other->name && (parent == nullptr || parent == _other->parent);
}

std::map<std::string, Type*>& Type::GetAllTypes()
{
    static std::map<std::string, Type*> allTypes;
    return allTypes;
}

std::map<int, Type*>& Type::GetAllTypesById()
{
    static std::map<int, Type*> allTypesById;
    return allTypesById;
}

TList<BaseField*>& Type::GetAllFields()
{
    return allFields;
}
//
// TList<BaseField*>& Type::StaticGetAllFields()
// {
//     static TList<BaseField*> staticAllFields;
//     return staticAllFields;
// }



Type* Type::GetType(const std::string& name)
{
    if (GetAllTypes().contains(name))
    {
        return GetAllTypes()[name];
    }
    return nullptr;
}

std::vector<Type*> Type::GetAllChildren(const Type& parent)
{
    std::vector<Type*> children;
    for (auto& [type_name, type] : GetAllTypes())
    {
        if (type->parent == &parent)
        {
            children.push_back(type);
        }
    }
    return children;
}

bool Type::IsOrIsDescendantOf(const Type* toCheck, const Type* parent)
{
    if (toCheck->Equals(parent))
    {
        return true;
    }

    Type* current = toCheck->parent;
    while (current != nullptr)
    {
        if (current->Equals(parent))
        {
            return true;
        }
        current = current->parent;
    }

    return false;
}
