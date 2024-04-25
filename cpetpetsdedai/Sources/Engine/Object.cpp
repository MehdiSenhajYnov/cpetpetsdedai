#include "../../Headers/Engine/Object.h"

std::map<std::string, Type*> Type::allTypes;
int Type::typeCount = 0;


Type::Type(const std::string& name, Type* parent): name(name), parent(parent)
{
	if (!allTypes.contains(name))
	{
		allTypes[name] = this;
		++typeCount;
	}
}

std::string Type::GetName()
{
	return name;
}

Type* Type::GetParent()
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

Type* Type::GetType(const std::string& name)
{
	if (allTypes.contains(name))
	{
		return allTypes[name];
	}
	return nullptr;
}

std::vector<Type*> Type::GetAllChildren(const Type& parent)
{
	std::vector<Type*> children;
	for (auto& [type_name, type] : allTypes)
	{
		if (type->parent == &parent)
		{
			children.push_back(type);
		}
	}
	return children;
}

bool Type::IsOrIsDescendantOf(const Type* child, const Type* parent)
{
	if (child->Equals(parent))
	{
		return true;
	}

	Type* current = child->parent;
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


Object::Object(std::string typeName, Type* parentType): type(typeName, parentType)
{
}

void Object::InitObject(std::string typeName, Type* parentType)
{
	type = Type(typeName, parentType);
}

Type* Object::GetType()
{
	return &type;
}
