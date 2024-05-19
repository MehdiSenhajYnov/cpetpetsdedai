#include "Type.h"
#include "Headers/Engine/Field.h"
#include "Headers/Engine/TypeContainer.h"

int Type::typeCount = 0;

Type::Type(const std::string& name, Type* parent): name(name), parent(parent)
{
    id = std::hash<std::string>{}(name);
    if (!TypeContainer::GetAllTypes().contains(name) || !TypeContainer::GetAllTypesById().contains(id))
    {
        TypeContainer::AddType(this, name, id);
        ++typeCount;
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
    GetAllFields().clear();
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
    if (_other == nullptr)
    {
        return false;
    }
    return name == _other->name && (parent == nullptr || parent == _other->parent);
}

bool Type::Equals(const Type* _other, const Type* _other2)
{
    if (_other == nullptr && _other2 == nullptr)
    {
        return true;
    }
    if (_other == nullptr || _other2 == nullptr)
    {
        return false;
    }
    return _other->Equals(_other2);
}

TList<BaseField*>& Type::GetAllFields()
{
    return allFields;
}

Type* Type::GetType(const std::string& name)
{
    if (TypeContainer::GetAllTypes().contains(name))
    {
        return TypeContainer::GetAllTypes()[name];
    }
    return nullptr;
}

std::vector<Type*> Type::GetAllChildren(const Type* parent)
{
    std::vector<Type*> children;
    for (auto& [type_name, type] : TypeContainer::GetAllTypes())
    {
        if (Equals(type->parent, parent))
        {
            children.push_back(type);
        }
    }
    return children;
}

std::vector<Type*> Type::GetAllChildrenRecursive(const Type* parent)
{
    std::vector<Type*> children;
    for (auto& [type_name, type] : TypeContainer::GetAllTypes())
    {
        if (Equals(type->parent, parent))
        {
            children.push_back(type);
            auto childrenOfChild = GetAllChildrenRecursive(type);
            children.insert(children.end(), childrenOfChild.begin(), childrenOfChild.end());
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
