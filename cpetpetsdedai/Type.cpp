#include "Type.h"


Type::Type(const std::string& name, Type* parent): name(name), parent(parent)
{
}

std::string Type::GetName()
{
	return name;
}

Type* Type::GetParent()
{
	return parent;
}

