#include "Object.h"

Type Object::objectType("Object", nullptr);

Object::Object(std::string typeName, Type* parentType): type(typeName, parentType)
{
}

Type* Object::ObjectType()
{
	return &objectType;
}
