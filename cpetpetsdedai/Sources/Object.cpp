#include "../Headers/Object.h"

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

Type* Type::GetType(const std::string& name, Type* parent)
{
	return nullptr;
}


Type Object::objectType("Object", nullptr);

Object::Object(std::string typeName, Type* parentType): type(typeName, parentType)
{
}

void Object::Init(std::string typeName, Type* parentType)
{
	type = Type(typeName, parentType);
}

Type* Object::GetType()
{
	return &type;
}

Type* Object::ObjectType()
{
	return &objectType;
}
